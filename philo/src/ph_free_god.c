/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_free_god.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:38:15 by teppei            #+#    #+#             */
/*   Updated: 2022/02/27 16:08:48 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_free_god(t_god *god, long n)
{
	long	i;

	i = -1;
	while (++i < n)
	{
		pthread_mutex_destroy(&god->forks[i]);
		pthread_mutex_destroy(&god->ph[i].have_eaten_mtx);
	}
	if (god->forks)
		free(god->forks);
	if (god->ph)
		free(god->ph);
}
