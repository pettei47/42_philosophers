/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_round_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:25:17 by teppei            #+#    #+#             */
/*   Updated: 2022/01/16 16:27:16 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ph_round_table(void *philo)
{
	t_philo	*p;

	p = philo;
	if (p->num % 2 == 0)
		usleep(10);
	while (1)
	{
		p->time_have_eaten = ph_get_time(0);
		usleep(50);
		fprintf(stderr, "philo[%lu]: end 1: %s\n", p->num, p->g->end ? "true" : "false");
		pthread_mutex_lock(&p->g->end_mtx);
		if (!p->g->end && p->num == p->g->num_of_philos)
		{
			printf("%ld %lu died(table)\n", ph_get_time(0), p->num);
			p->g->end = true;
			pthread_mutex_unlock(&p->g->end_mtx);
			break ;
		}
		else if (p->g->end)
		{
			pthread_mutex_unlock(&p->g->end_mtx);
			break ;
		}
		fprintf(stderr, "philo[%lu]: end 2: %s\n", p->num, p->g->end ? "true" : "false");
		pthread_mutex_unlock(&p->g->end_mtx);
	}
	return (NULL);
}
