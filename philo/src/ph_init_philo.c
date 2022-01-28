/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 13:41:37 by teppei            #+#    #+#             */
/*   Updated: 2022/01/28 21:36:59 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ph_init_philos(t_god *god)
{
	long	i;

	god->ph = (t_philo *)malloc(sizeof(t_philo) * god->num_of_philos);
	if (!god->ph)
		return (false);
	god->start_time = ph_get_time(0);
	i = -1;
	while (++i < (long)god->num_of_philos)
	{
		god->ph[i].num = i + 1;
		god->ph[i].l_fork = i;
		if (i + 1 == (long)god->num_of_philos)
			god->ph[i].r_fork = 0;
		else
			god->ph[i].r_fork = i + 1;
		god->ph[i].time_have_eaten = god->start_time;
		god->ph[i].eat_count = 0;
		god->ph[i].g = god;
	}
	return (true);
}
