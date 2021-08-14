/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 00:02:19 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/06/29 00:02:27 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_pthreads_join(pthread_t ph, t_phil_struct **phils)
{
	int	i;

	if (pthread_join(ph, NULL) != 0)
		return (0);
	usleep(30);
	i = -1;
	while (++i < phils[0]->init_data->num_phils)
	{
		if (pthread_join(phils[i]->ph, NULL) != 0)
			return (0);
		usleep(30);
		pthread_mutex_destroy(phils[i]->left_ph);
	}
	return (1);
}

void	sleeping_thinking(t_phil_struct	*temp)
{
	if (temp->finished != 1 && !temp->init_data->end_flag)
	{
		message(temp, "is sleeping");
		ft_to_sleep(temp->init_data, temp->init_data->tt_sleep);
		message(temp, "is thinking");
	}
}

void	*eating(void *phils)
{
	t_phil_struct	*temp;

	temp = (t_phil_struct *) phils;
	while (temp->finished != 1 && !temp->init_data->end_flag)
	{
		pthread_mutex_lock(temp->left_ph);
		message(temp, "has taken a fork");
		pthread_mutex_lock(temp->right_ph);
		message(temp, "has taken a fork");
		message(temp, "is eating");
		pthread_mutex_lock(temp->init_data->to_stop);
		temp->t_must_die = get_current_time() + temp->init_data->tt_die;
		pthread_mutex_unlock(temp->init_data->to_stop);
		ft_to_sleep(temp->init_data, temp->init_data->tt_eat);
		temp->has_eaten++;
		if (temp->has_eaten >= temp->init_data->num_meals)
			temp->finished = 1;
		pthread_mutex_unlock(temp->left_ph);
		pthread_mutex_unlock(temp->right_ph);
		sleeping_thinking(temp);
	}
	temp->init_data->end_flag = 1;
	return (NULL);
}

void	*is_alive(void	*phils)
{
	int				i;
	int				k;
	t_phil_struct	**temp;

	temp = phils;
	i = 0;
	k = temp[i]->init_data->num_phils;
	while (!temp[0]->init_data->end_flag)
	{
		if (i == k)
			i = 0;
		pthread_mutex_lock(temp[i]->init_data->to_stop);
		if (get_current_time() - 5 > temp[i]->t_must_die)
		{
			message(temp[i], "died");
			temp[i]->init_data->end_flag = 1;
			pthread_mutex_unlock(temp[i]->init_data->to_stop);
			break ;
		}
		pthread_mutex_unlock(temp[i]->init_data->to_stop);
		i++;
	}
	return (NULL);
}

int	ft_start_threads(t_phil_struct **phils)
{
	int			i;
	int			k;
	pthread_t	ph;

	k = phils[0]->init_data->num_phils;
	i = -1;
	while (++i < k)
		pthread_mutex_init(phils[i]->left_ph, NULL);
	i = -1;
	if (pthread_create(&ph, NULL, is_alive, (void *)phils) != 0)
		return (0);
	while (++i < k)
	{
		if (pthread_create(&phils[i]->ph, NULL, eating, (void *)phils[i]) != 0)
			return (0);
		usleep(40);
	}
	if (!ft_pthreads_join(ph, phils))
		return (0);
	return (1);
}
