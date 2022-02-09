/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:27:41 by teppei            #+#    #+#             */
/*   Updated: 2022/02/09 22:38:05 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_thread_error(t_philo *p, t_god *g, long num_of_philos)
{
	long	i;

	i = -1;
	pthread_mutex_lock(&g->end_mtx);
	g->end = true;
	pthread_mutex_unlock(&g->end_mtx);
	while (++i < num_of_philos)
	{
		if (pthread_detach(p[i].th) != 0)
			return (ph_error(1, E_JOIN"philo", g, g->num_of_philos));
	}
	return (ph_error(1, E_CRTH"philo", g, g->num_of_philos));
}

int	ph_thread_control(t_god *g)
{
	long	i;

	i = -1;
	g->end = false;
	g->start_time = ph_get_time(0);
	while (++i < (long)g->num_of_philos)
	{
		if (pthread_create(&g->ph[i].th, NULL, &ph_round_table, &g->ph[i]) != 0)
			return (ph_thread_error(g->ph, g, i));
	}
	if (pthread_create(&g->monitor, NULL, &ph_monitor, g) != 0)
		return (ph_thread_error(g->ph, g, i));
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
