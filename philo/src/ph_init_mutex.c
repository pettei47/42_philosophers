/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 13:43:38 by teppei            #+#    #+#             */
/*   Updated: 2022/03/13 08:27:29 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ph_init_mutex(t_god *god)
{
	long	i;

	i = -1;
	god->forks = (pthread_mutex_t *)malloc(\
				sizeof(pthread_mutex_t) * god->num_of_philos);
	god->fork_state = (bool *)malloc(sizeof(bool) * god->num_of_philos);
	if (!god->forks || !god->fork_state)
		return (false);
	while (++i < (long)god->num_of_philos)
	{
		if (pthread_mutex_init(&god->forks[i], NULL) != 0)
			return (ph_error(0, NULL, god, i));
		god->fork_state[i] = false;
	}
	if (pthread_mutex_init(&god->end_mtx, NULL) != 0)
		return (ph_error(0, NULL, god, god->num_of_philos));
	return (true);
}
