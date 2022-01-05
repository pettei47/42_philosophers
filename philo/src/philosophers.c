/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:24:46 by teppei            #+#    #+#             */
/*   Updated: 2022/01/05 21:33:12 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ph_init_philos(t_god *god)
{
	long	i;

	god->ph = (t_philo *)malloc(sizeof(t_philo) * god->num_of_philos);
	if (!god->ph)
		return (false);
	i = -1;
	while (++i < (long)god->num_of_philos)
	{
		god->ph[i].num = i + 1;
		god->ph[i].l_fork = i;
		if (i + 1 == (long)god->num_of_philos)
			god->ph[i].r_fork = 0;
		else
			god->ph[i].r_fork = i + 1;
		god->ph[i].time_have_eaten = 0;
		god->ph[i].eat_count = 0;
	}
	return (true);
}

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

bool	ph_error_destroy(t_god *god, long n)
{
	(void)n;
	(void)god;
	//ph_free_god(god, n);
	return (false);
}

bool	ph_init_mutex(t_god *god)
{
	long	i;

	i = -1;
	god->forks = (pthread_mutex_t *)malloc(\
				sizeof(pthread_mutex_t) * god->num_of_philos);
	if (!god->forks)
		return (false);
	while (++i < (long)god->num_of_philos)
	{
		if (pthread_mutex_init(&god->forks[i], NULL) != 0)
			return (ph_error_destroy(god, i));
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_god	god;

	if (ac < 5 || 6 < ac)
		return (ph_error(1, USAGE));
	if (!ph_check_args(av, &god))
		return (ph_error(1, E_ARGS));
	if (!ph_init_philos(&god))
		return (ph_error(1, "failed to init_philo"));
	if (!ph_init_mutex(&god))
		return (ph_error(1, "failed to init mutex"));
	//ph_free_god(&god, god.num_of_philos);
	system("leaks philo");
	return (0);
}
