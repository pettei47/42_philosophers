/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:54:45 by teppei            #+#    #+#             */
/*   Updated: 2022/03/13 08:18:42 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_STRUCT_H
# define PH_STRUCT_H

# include "philosophers.h"

enum	e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
};

typedef struct s_god	t_god;
typedef struct s_philo
{
	unsigned long	num;
	unsigned long	l_fork;
	unsigned long	r_fork;
	unsigned long	time_have_eaten;
	pthread_mutex_t	have_eaten_mtx;
	unsigned long	eat_count;
	pthread_t		th;
	t_god			*g;
}	t_philo;

typedef struct s_god
{
	unsigned long	num_of_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	num_of_must_eat;
	unsigned long	start_time;
	pthread_mutex_t	*forks;
	bool			*fork_state;
	unsigned long	num_of_have_eaten;
	bool			end;
	pthread_mutex_t	end_mtx;
	pthread_t		monitor;
	t_philo			*ph;
}	t_god;

#endif
