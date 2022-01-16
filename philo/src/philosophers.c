/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:24:46 by teppei            #+#    #+#             */
/*   Updated: 2022/01/16 16:30:04 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
