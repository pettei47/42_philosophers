/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 01:48:25 by teppei            #+#    #+#             */
/*   Updated: 2022/02/07 22:03:05 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putendl_fd(char *s, int fd)
{
	long	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
	write(fd, "\n", 1);
}

int	ph_error(int ret, char *err, t_god *god, long n)
{
	if (god)
		ph_free_god(god, n);
	if (err)
		ft_putendl_fd(err, 2);
	//後で消す
	system("leaks philo");
	return (ret);
}
