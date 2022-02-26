/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_round_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:25:17 by teppei            #+#    #+#             */
/*   Updated: 2022/02/26 23:04:45 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ph_print_action(t_philo *p, t_god *g, int act, long i)
{
	pthread_mutex_lock(&g->end_mtx);
	if (act == FORK && !g->end)
		printf("%ld %lu"FORK_MSG, ph_get_time(g->start_time), p->num);
	else if (act == SLEEP && !g->end)
		printf("%ld %lu"SLEEP_MSG, ph_get_time(g->start_time), p->num);
	else if (act == THINK && !g->end)
		printf("%ld %lu"THINK_MSG, ph_get_time(g->start_time), p->num);
	else if (!g->end)
	{
		printf("%ld %lu"EAT_MSG, ph_get_time(g->start_time), p->num);
		p->time_have_eaten = ph_get_time(0);
		pthread_mutex_unlock(&g->end_mtx);
		while (++i < (long)g->time_to_eat && !g->end)
			usleep(1000);
		p->time_have_eaten = ph_get_time(0);
		pthread_mutex_lock(&g->end_mtx);
		p->eat_count++;
		if (p->eat_count == g->num_of_must_eat)
			g->num_of_have_eaten++;
		if (g->num_of_have_eaten == g->num_of_philos)
			g->end = true;
	}
	pthread_mutex_unlock(&g->end_mtx);
	return (g->end == false && g->num_of_philos != 1);
}

bool	ph_eat(t_philo *p, t_god *g, pthread_mutex_t *f, unsigned long *forks)
{
	pthread_mutex_lock(&f[forks[0]]);
	if (ph_get_time(p->time_have_eaten) > (long)g->time_to_die)
	{
		pthread_mutex_lock(&g->end_mtx);
		if (!g->end)
			printf("%ld %lu died\n", ph_get_time(g->start_time), p->num);
		g->end = true;
		return (ph_unlock(&g->end_mtx, &f[forks[0]], false));
	}
	if (!ph_print_action(p, g, FORK, -1))
		return (ph_unlock(&f[forks[0]], NULL, false));
	pthread_mutex_lock(&f[forks[1]]);
	if (ph_get_time(p->time_have_eaten) > (long)g->time_to_die)
	{
		ph_unlock(&f[forks[0]], &f[forks[1]], false);
		pthread_mutex_lock(&g->end_mtx);
		if (!g->end)
			printf("%ld %lu died\n", ph_get_time(g->start_time), p->num);
		g->end = true;
		return (ph_unlock(&g->end_mtx, NULL, false));
	}
	if (!ph_print_action(p, g, FORK, -1) || !ph_print_action(p, g, EAT, -1))
		return (ph_unlock(&f[forks[0]], &f[forks[1]], false));
	return (ph_unlock(&f[forks[0]], &f[forks[1]], g->end == false));
}

bool	ph_sleep(t_philo *p, t_god *g, long i)
{
	if (g->end)
		return (false);
	if (!ph_print_action(p, g, SLEEP, -1))
		return (false);
	while (++i < (long)g->time_to_sleep && !g->end)
		usleep(1000);
	pthread_mutex_lock(&g->end_mtx);
	if (ph_get_time(p->time_have_eaten) > (long)g->time_to_die)
	{
		if (!g->end)
			printf("%ld %lu died\n", ph_get_time(g->start_time), p->num);
		g->end = true;
		return (ph_unlock(&g->end_mtx, NULL, false));
	}
	return (ph_unlock(&g->end_mtx, NULL, true));
}

bool	ph_think(t_philo *p, t_god *g)
{
	long	thiking_time;
	long	buffer_time;

	if (g->end)
		return (false);
	buffer_time = g->num_of_philos * 10;
	thiking_time = 0.1 * \
		(g->time_to_die - g->time_to_eat - g->time_to_sleep - buffer_time);
	if (thiking_time < 10 || thiking_time > (long)g->time_to_die)
		thiking_time = 10;
	if (!ph_print_action(p, g, THINK, -1))
		return (false);
	while (thiking_time-- && !g->end)
		usleep(1000);
	pthread_mutex_lock(&g->end_mtx);
	if (ph_get_time(p->time_have_eaten) > (long)g->time_to_die)
	{
		if (!g->end)
			printf("%ld %lu died\n", ph_get_time(g->start_time), p->num);
		g->end = true;
		return (ph_unlock(&g->end_mtx, NULL, false));
	}
	return (ph_unlock(&g->end_mtx, NULL, true));
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
			!ph_sleep(p, g, -1) || !ph_think(p, g))
			break ;
	}
	return (NULL);
}
