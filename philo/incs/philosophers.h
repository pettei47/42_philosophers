/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:26:53 by teppei            #+#    #+#             */
/*   Updated: 2022/01/05 01:55:08 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include "ph_struct.h"

# define USAGE	"usage: ./philo number_of_philosophers time_to_die \n\
\ttime_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define E_ARGS	"error: invalid argments"

int		ph_error(int ret, char *err);
bool	ph_check_args(char **av, t_god *god);

#endif
