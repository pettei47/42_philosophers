/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:28:40 by teppei            #+#    #+#             */
/*   Updated: 2022/01/16 16:28:53 by teppei           ###   ########.fr       */
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
			printf("%ld %lu died(monitor)\n", ph_get_time(0), p[i].num);
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
		fprintf(stderr, "monitor: end: %s\n", g->end ? "true" : "false");
		pthread_mutex_lock(&g->end_mtx);
		if (g->end)
			break ;
		ph_dead_cheack(g, g->ph);
		pthread_mutex_unlock(&g->end_mtx);
		fprintf(stderr, "monitor 2: end_mtx: %p\n", &g->end_mtx);
	}
	pthread_mutex_unlock(&g->end_mtx);
	return (NULL);
}
