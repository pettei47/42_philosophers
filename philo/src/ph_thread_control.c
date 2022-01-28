/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:27:41 by teppei            #+#    #+#             */
/*   Updated: 2022/01/28 20:23:35 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_thread_control(t_god *g)
{
	long	i;

	i = -1;
	g->end = false;
	g->start_time = ph_get_time(0);
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
