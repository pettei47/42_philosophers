/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:54:45 by teppei            #+#    #+#             */
/*   Updated: 2022/01/05 01:53:23 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_STRUCT_H
# define PH_STRUCT_H

# include "philosophers.h"

typedef struct s_god	t_god;
typedef struct s_philo
{
	unsigned long	num;
	unsigned long	l_fork;
	unsigned long	r_fork;
	unsigned long	time_have_eaten;
	unsigned long	eat_count;
	t_god			*g;
}	t_philo;


typedef struct s_god
{
	unsigned long	num_of_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	num_of_must_eat;
	pthread_mutex_t	*forks;
	t_philo			*ph;
}	t_god;

// typedef struct s_data	t_data;
// typedef struct s_philo
// {
// 	int				eat_count;
// 	int				num;
// 	int				l_fork;
// 	int				r_fork;
// 	size_t			last_eat_time;
// 	pthread_t		thread;
// 	t_data			*d;
// }	t_philo;

// typedef struct s_data
// {
// 	int				philo_num;
// 	size_t			die_time;
// 	size_t			eat_time;
// 	size_t			sleep_time;
// 	int				max_eat_num;
// 	int				fork_num;
// 	int				end_flag;
// 	int				philos_eat_count;
// 	pthread_mutex_t	*fork;
// 	pthread_mutex_t	common_protect;
// 	pthread_t		starvation_monitor;
// 	t_philo			*philo;
// }	t_data;



#endif
