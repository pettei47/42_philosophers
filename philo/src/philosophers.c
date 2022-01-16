/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:24:46 by teppei            #+#    #+#             */
/*   Updated: 2022/01/16 13:20:18 by teppei           ###   ########.fr       */
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
		god->ph[i].g = god;
	}
	return (true);
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
			return (ph_error(0, NULL, god, i));
	}
	if (pthread_mutex_init(&god->end_mtx, NULL) != 0)
		return (ph_error(0, NULL, god, god->num_of_philos));
	return (true);
}

long	ph_get_time(unsigned long t)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - t);
}

void	ph_dead_cheack(t_god *g, t_philo *p)
{
	long	i;

	i = -1;
	while (++i < (long)g->num_of_philos)
	{
		if (g->end)
			return ;
		if (ph_get_time(p[i].time_have_eaten) > (long)g->time_to_die)
		{
			printf("%ld %lu died\n", ph_get_time(0), p[i].num);
			g->end = true;
			return ;
		}
	}
}

void	*ph_monitor(void *god)
{
	t_god	*g;

	g = (t_god *)god;
	fprintf(stderr, "start: monitor\n");
	while (1)
	{
		usleep(5);
		pthread_mutex_lock(&g->end_mtx);
		if (g->end)
			break ;
		ph_dead_cheack(g, g->ph);
		pthread_mutex_unlock(&g->end_mtx);
	}
	fprintf(stderr, "done: monitor\n");
	return (NULL);
}

void	*ph_round_table(void *philo)
{
	t_philo	*p;

	p = philo;
	// if (p->num % 2 == 0)
	// 	usleep((p->g->time_to_eat * 100) / 10);
	// while (1)
	// {
	// 	if ()
	// }
	p->time_have_eaten = 1000;
	usleep(50);
	if (p->num == p->g->num_of_philos)
	{
		pthread_mutex_lock(&p->g->end_mtx);
		printf("%ld %lu died\n", ph_get_time(0), p->num);
		p->g->end = true;
		pthread_mutex_unlock(&p->g->end_mtx);
	}
	return (NULL);
}

int	ph_thread_control(t_god *g)
{
	long	i;

	i = -1;
	g->end = false;
	while (++i < (long)g->num_of_philos)
	{
		if (pthread_create(&g->ph[i].th, NULL, &ph_round_table, &g->ph[i]) != 0)
			return (ph_error(1, E_CRTH"philo", g, g->num_of_philos));
	}
	if (pthread_create(&g->monitor, NULL, &ph_monitor, g) != 0)
		return (ph_error(1, E_CRTH"monitor", g, g->num_of_philos));
	i = -1;
	while (++i < (long)g->num_of_philos)
	{
		if (pthread_join(g->ph[i].th, NULL) != 0)
			return (ph_error(1, E_JOIN"philo", g, g->num_of_philos));
	}
	if (pthread_join(g->monitor, NULL) != 0)
		return (ph_error(1, E_JOIN"monitor", g, g->num_of_philos));
	return (0);
}

int	main(int ac, char **av)
{
	t_god	god;

	if (ac < 5 || 6 < ac)
		return (ph_error(1, USAGE, NULL, 0));
	if (!ph_check_args(av, &god))
		return (ph_error(1, E_ARGS, NULL, 0));
	if (!ph_init_philos(&god))
		return (ph_error(1, E_INIT"philo", NULL, 0));
	if (!ph_init_mutex(&god))
		return (ph_error(1, E_INIT"mutex", NULL, 0));
	fprintf(stderr, "init done\n");
	if (ph_thread_control(&god) == 0)
		ph_free_god(&god, god.num_of_philos);
	system("leaks philo");
	return (0);
}
