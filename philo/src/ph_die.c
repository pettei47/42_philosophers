/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_die.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 09:46:29 by teppei            #+#    #+#             */
/*   Updated: 2022/03/13 09:46:59 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ph_die(t_philo *p, t_god *g)
{
	pthread_mutex_lock(&g->end_mtx);
	if (!g->end)
		printf("%ld %lu died(die)\n", ph_get_time(g->start_time), p->num);
	g->end = true;
	pthread_mutex_unlock(&g->end_mtx);
	return (false);
}
