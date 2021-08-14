/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 00:00:50 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/06/29 00:01:09 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	message(t_phil_struct *phils, char *str)
{
	if (phils->init_data->end_flag == 1)
		return (1);
	if (pthread_mutex_lock(phils->init_data->for_print) != 0)
		return (0);
	printf("%ld %d %s\n", get_current_time() - phils->init_data->start,
		phils->id, str);
	if (pthread_mutex_unlock(phils->init_data->for_print) != 0)
		return (0);
	return (1);
}

int	ft_to_sleep(t_id_struct *init_data, long n)
{
	long	time;

	time = get_current_time() - init_data->start + n;
	if (time == n - 1)
		return (0);
	while (get_current_time() - init_data->start < time)
		usleep(100);
	return (1);
}
