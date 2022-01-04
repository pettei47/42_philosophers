/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 01:49:25 by teppei            #+#    #+#             */
/*   Updated: 2022/01/05 01:49:49 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ph_strdigit(char *s)
{
	long	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] < '0' || '9' < s[i])
			return (false);
	}
	return (true);
}

unsigned long	ph_atol(char *s)
{
	long			i;
	unsigned long	nbr;

	i = 0;
	nbr = 0;
	if (!s || s[0] == '-' || !ph_strdigit(s))
		return (0);
	while ('0' <= s[i] && s[i] <= '9')
	{
		nbr = nbr * 10 + (s[i++] - '0');
		if (nbr != nbr * 10 / 10)
			return (__LONG_MAX__);
	}
	return (nbr);
}

bool	ph_check_args(char **av, t_god *god)
{
	size_t	i;

	i = 1;
	god->num_of_philos = ph_atol(av[i++]);
	god->time_to_die = ph_atol(av[i++]);
	god->time_to_eat = ph_atol(av[i++]);
	god->time_to_sleep = ph_atol(av[i++]);
	god->num_of_must_eat = ph_atol(av[i]);
	if (!god->num_of_philos || !god->time_to_die || !god->time_to_eat ||
		!god->time_to_sleep || (!god->num_of_must_eat && av[i]))
		return (false);
	return (true);
}
