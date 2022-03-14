/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_round_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:25:17 by teppei            #+#    #+#             */
/*   Updated: 2022/03/13 18:06:09 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_check_eat_count(t_philo *p, t_god *g)
{
	if (++p->eat_count == g->num_of_must_eat)
		g->num_of_have_eaten++;
	if (g->num_of_have_eaten == g->num_of_philos)
		g->end = true;
}

bool	ph_print_action(t_philo *p, t_god *g, int act)
{
	int	fork_2;

	fork_2 = p->num;
	if (p->num == g->num_of_philos)
		fork_2 = 0;
	pthread_mutex_lock(&g->end_mtx);
	if (act == FORK && !g->end)
		printf("%ld %lu"FORK_MSG, ph_get_time(g->start_time), p->num);
	else if (act == SLEEP && !g->end)
		printf("%ld %lu"SLEEP_MSG, ph_get_time(g->start_time), p->num);
	else if (act == THINK && !g->end)
		printf("%ld %lu"THINK_MSG, ph_get_time(g->start_time), p->num);
	else if (!g->end && g->fork_state[p->num - 1] && g->fork_state[fork_2])
	{
		p->time_have_eaten = ph_get_time(0);
		printf("%ld %lu"EAT_MSG, ph_get_time(g->start_time), p->num);
		g->fork_state[p->num - 1] = false;
		g->fork_state[fork_2] = false;
		ph_check_eat_count(p, g);
		pthread_mutex_unlock(&g->end_mtx);
		ph_time_count(g, p->time_have_eaten, g->time_to_eat);
		return (g->end == false);
	}
	pthread_mutex_unlock(&g->end_mtx);
	return (g->end == false && g->num_of_philos != 1);
}

bool	ph_eat(t_philo *p, t_god *g, pthread_mutex_t *f, unsigned long *forks)
{
	pthread_mutex_lock(&f[forks[0]]);
	g->fork_state[forks[0]] = true;
	if (ph_get_time(p->time_have_eaten) > (long)g->time_to_die)
	{
		g->fork_state[forks[0]] = false;
		ph_die(p, g);
		return (ph_unlock(&f[forks[0]], NULL, false));
	}
	if (!ph_print_action(p, g, FORK))
		return (ph_unlock(&f[forks[0]], NULL, false));
	pthread_mutex_lock(&f[forks[1]]);
	g->fork_state[forks[1]] = true;
	if (ph_get_time(p->time_have_eaten) > (long)g->time_to_die)
	{
		g->fork_state[forks[1]] = false;
		ph_die(p, g);
		return (ph_unlock(&f[forks[0]], &f[forks[1]], false));
	}
	if (!ph_print_action(p, g, FORK) || !ph_print_action(p, g, EAT))
		return (ph_unlock(&f[forks[0]], &f[forks[1]], false));
	return (ph_unlock(&f[forks[0]], &f[forks[1]], g->end == false));
}

bool	ph_sleep_or_think(t_philo *p, t_god *g, int action)
{
	long	thinking_time;
	long	time_to_spend;

	if (g->end)
		return (false);
	thinking_time = 0.1 * (g->time_to_die - g->time_to_eat - g->time_to_sleep);
	if (thinking_time < 10 || thinking_time > (long)g->time_to_die)
		thinking_time = 10;
	time_to_spend = thinking_time;
	if (action == SLEEP)
		time_to_spend = g->time_to_sleep;
	if (!ph_print_action(p, g, action))
		return (false);
	ph_time_count(g, ph_get_time(0), time_to_spend);
	if (ph_get_time(p->time_have_eaten) > (long)g->time_to_die && !g->end)
		return (ph_die(p, g));
	return (!g->end);
}

void	*ph_round_table(void *philo)
{
	t_god			*g;
	t_philo			*p;
	unsigned long	forks[2];

	p = philo;
	g = p->g;
	forks[0] = p->l_fork;
	forks[1] = p->r_fork;
	if (p->num % 2 == 0)
	{
		forks[0] = p->r_fork;
		forks[1] = p->l_fork;
		usleep(200);
	}
	p->time_have_eaten = ph_get_time(0);
	while (!g->end)
	{
		if (g->end || !ph_eat(p, g, g->forks, forks) || \
			!ph_sleep_or_think(p, g, SLEEP) || \
			!ph_sleep_or_think(p, g, THINK))
			break ;
	}
	return (NULL);
}
