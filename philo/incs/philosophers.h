/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:26:53 by teppei            #+#    #+#             */
/*   Updated: 2022/03/13 18:02:48 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include "ph_struct.h"

# define USAGE		"usage: ./philo number_of_philosophers time_to_die \n\
\ttime_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define E_ARGS		"error: invalid argments"
# define E_INIT		"failed to init: "
# define E_CRTH		"failed to create thread: "
# define E_JOIN		"failed to join: "

# define FORK_MSG	" has taken a fork\n"
# define EAT_MSG	" is eating\n"
# define SLEEP_MSG	" is sleeping\n"
# define THINK_MSG	" is thinking\n"

int		ph_error(int ret, char *err, t_god *god, long n);
bool	ph_check_args(char **av, t_god *god);
void	ph_free_god(t_god *god, long n);
bool	ph_init_philos(t_god *god);
bool	ph_init_mutex(t_god *god);
long	ph_get_time(unsigned long t);
int		ph_thread_control(t_god *g);
void	*ph_round_table(void *philo);
void	*ph_monitor(void *god);
bool	ph_die(t_philo *p, t_god *g);
void	ph_time_count(t_god *g, long start, long time);
bool	ph_unlock(pthread_mutex_t *mtx1, pthread_mutex_t *mtx2, bool ret);

#endif
