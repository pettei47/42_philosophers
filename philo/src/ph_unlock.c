/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_unlock.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 21:15:14 by teppei            #+#    #+#             */
/*   Updated: 2022/01/28 21:15:43 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ph_unlock(pthread_mutex_t *mtx1, pthread_mutex_t *mtx2, bool ret)
{
	if (mtx1)
		pthread_mutex_unlock(mtx1);
	if (mtx2)
		pthread_mutex_unlock(mtx2);
	return (ret);
}
