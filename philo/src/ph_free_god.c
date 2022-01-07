/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_free_god.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:38:15 by teppei            #+#    #+#             */
/*   Updated: 2022/01/08 00:44:43 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_free_god(t_god *god, long n)
{
	long	i;

	i = -1;
	while (++i < n)
		pthread_mutex_destroy(&god->forks[i]);
	if (god->forks)
		free(god->forks);
	if (god->ph)
		free(god->ph);
}
