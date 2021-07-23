/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 00:00:50 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/06/29 00:01:09 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_message(t_phil_struct *phils, char *str)
{
	if (sem_wait(phils->init_data->for_print) != 0)
		return (0);
	printf(YELLOW"%ld %d %s\n", ft_get_current_time() - phils->init_data->start,
		phils->id, str);
	if (ft_strncmp(str, "died", 4))
		if (sem_post(phils->init_data->for_print) != 0)
			return (0);
	return (1);
}

int	ft_to_sleep(t_id_struct *init_data, long n)
{
	long	time;

	time = ft_get_current_time() - init_data->start + n;
	if (time == n - 1)
		return (0);
	while (ft_get_current_time() - init_data->start < time)
		usleep(100);
	return (1);
}

void	ft_sem_closes(t_phil_struct **phils)
{
	int	i;

	i = -1;
	while (++i < phils[0]->init_data->num_phils)
		sem_close(phils[i]->finished);
	sem_close(phils[0]->init_data->for_print);
	sem_close(phils[0]->init_data->fork);
	sem_close(phils[0]->init_data->kill);
}

int	ft_one_phil(t_id_struct *init_data)
{
	if (sem_wait(init_data->for_print))
		return (0);
	printf(YELLOW"%ld 1 has taken a fork\n",
		   ft_get_current_time() - init_data->start);
	printf(YELLOW"%d 1 died\n", init_data->tt_die);
	if (sem_post(init_data->for_print))
		return (0);
	return (2);
}
