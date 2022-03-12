/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:28:40 by teppei            #+#    #+#             */
/*   Updated: 2022/02/27 16:20:10 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ph_dead_cheack(t_god *g, t_philo *p)
{
	long	i;

	i = -1;
	while (++i < (long)g->num_of_philos)
	{
		if (g->end)
			return (true);
		pthread_mutex_lock(&p[i].have_eaten_mtx);
		if (ph_get_time(p[i].time_have_eaten) > (long)g->time_to_die)
		{
			printf("%ld %lu died\n", ph_get_time(g->start_time), p[i].num);
			g->end = true;
			return (true);
		}
		pthread_mutex_unlock(&p[i].have_eaten_mtx);
	}
	return (false);
}

void	*ph_monitor(void *god)
{
	t_god	*g;

	g = (t_god *)god;
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&g->end_mtx);
		if (ph_dead_cheack(g, g->ph))
			break ;
		pthread_mutex_unlock(&g->end_mtx);
	}
	pthread_mutex_unlock(&g->end_mtx);
	return (NULL);
}
