/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:24:46 by teppei            #+#    #+#             */
/*   Updated: 2022/01/16 13:46:04 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_dead_cheack(t_god *g, t_philo *p)
{
	long	i;

	i = -1;
	while (++i < (long)g->num_of_philos)
	{
		if (g->end)
			return ;
		if (ph_get_time(p[i].time_have_eaten) > (long)g->time_to_die)
		{
			printf("%ld %lu died\n", ph_get_time(0), p[i].num);
			g->end = true;
			return ;
		}
	}
}

void	*ph_monitor(void *god)
{
	t_god	*g;

	g = (t_god *)god;
	while (1)
	{
		usleep(5);
		if (g->end)
			break ;
		pthread_mutex_lock(&g->end_mtx);
		ph_dead_cheack(g, g->ph);
		pthread_mutex_unlock(&g->end_mtx);
	}
	return (NULL);
}

void	*ph_round_table(void *philo)
{
	t_philo	*p;

	p = philo;
	// if (p->num % 2 == 0)
	// 	usleep((p->g->time_to_eat * 100) / 10);
	// while (1)
	// {
	// 	if ()
	// }
	p->time_have_eaten = ph_get_time(0);
	usleep(50);
	if (!p->g->end && p->num == p->g->num_of_philos)
	{
		pthread_mutex_lock(&p->g->end_mtx);
		printf("%ld %lu died\n", ph_get_time(0), p->num);
		p->g->end = true;
		pthread_mutex_unlock(&p->g->end_mtx);
	}
	return (NULL);
}

int	ph_thread_control(t_god *g)
{
	long	i;

	i = -1;
	g->end = false;
	while (++i < (long)g->num_of_philos)
	{
		if (pthread_create(&g->ph[i].th, NULL, &ph_round_table, &g->ph[i]) != 0)
			return (ph_error(1, E_CRTH"philo", g, g->num_of_philos));
	}
	if (pthread_create(&g->monitor, NULL, &ph_monitor, g) != 0)
		return (ph_error(1, E_CRTH"monitor", g, g->num_of_philos));
	i = -1;
	while (++i < (long)g->num_of_philos)
	{
		if (pthread_join(g->ph[i].th, NULL) != 0)
			return (ph_error(1, E_JOIN"philo", g, g->num_of_philos));
	}
	if (pthread_join(g->monitor, NULL) != 0)
		return (ph_error(1, E_JOIN"monitor", g, g->num_of_philos));
	return (0);
}

int	main(int ac, char **av)
{
	t_god	god;

	if (ac < 5 || 6 < ac)
		return (ph_error(1, USAGE, NULL, 0));
	if (!ph_check_args(av, &god))
		return (ph_error(1, E_ARGS, NULL, 0));
	if (!ph_init_philos(&god))
		return (ph_error(1, E_INIT"philo", NULL, 0));
	if (!ph_init_mutex(&god))
		return (ph_error(1, E_INIT"mutex", NULL, 0));
	fprintf(stderr, "init done\n");
	if (ph_thread_control(&god) == 0)
		ph_free_god(&god, god.num_of_philos);
	system("leaks philo");
	return (0);
}
