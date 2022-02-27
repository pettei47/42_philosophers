/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 13:43:38 by teppei            #+#    #+#             */
/*   Updated: 2022/02/27 16:15:55 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ph_init_mutex(t_god *god)
{
	long	i;
	int		init_fork;
	int		init_have;

	i = -1;
	god->forks = (pthread_mutex_t *)malloc(\
				sizeof(pthread_mutex_t) * god->num_of_philos);
	if (!god->forks)
		return (false);
	while (++i < (long)god->num_of_philos)
	{
		init_fork = pthread_mutex_init(&god->forks[i], NULL);
		init_have = pthread_mutex_init(&god->ph[i].have_eaten_mtx, NULL);
		if (init_fork || init_have)
			return (ph_error(0, NULL, god, i));
	}
	if (pthread_mutex_init(&god->end_mtx, NULL) != 0)
		return (ph_error(0, NULL, god, god->num_of_philos));
	return (true);
}
