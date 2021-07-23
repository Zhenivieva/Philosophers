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

int	count_meals(t_phil_struct *temp)
{
	int	n;

	n = 1;
	if (temp->init_data->num_meals)
	{
		if (sem_wait(temp->init_data->for_print))
			return (0);
		if (temp->has_eaten == temp->init_data->num_meals)
		{
			sem_post(temp->finished);
			n--;
		}
		if (sem_post(temp->init_data->for_print))
			return (0);
	}
	return (n);
}

void	*ft_is_alive(void *phils)
{
	t_phil_struct	*temp;

	temp = phils;
	if (pthread_detach(temp->ph))
		pthread_exit(0);
	while (1)
	{
		if (ft_get_current_time() - 5 > temp->t_must_die)
		{
			ft_message(temp, "died");
			sem_post(temp->init_data->kill);
			pthread_exit(0);
		}
	}
}

void	*ft_eating(void *phils)
{
	t_phil_struct	*temp;

	temp = phils;
	if (pthread_create(&temp->ph, NULL, ft_is_alive, (void *)temp) != 0)
		return (0);
	while (1)
	{
		if (sem_wait(temp->init_data->fork) || sem_wait(temp->init_data->fork))
			exit(0);
		temp->t_must_die = ft_get_current_time() + temp->init_data->tt_die;
		ft_message(temp, "has taken a fork");
		ft_message(temp, "has taken a fork");
		ft_message(temp, "is eating");
		ft_to_sleep(temp->init_data, temp->init_data->tt_eat);
		if (sem_post(temp->init_data->fork) || sem_post(temp->init_data->fork))
			exit(0);
		if (++temp->has_eaten && !count_meals(temp))
			exit(0);
		ft_message(temp, "is sleeping");
		ft_to_sleep(temp->init_data, temp->init_data->tt_sleep);
		ft_message(temp, "is thinking");
	}
}

void	*ft_count_eat(void *phils)
{
	int				i;
	t_phil_struct	**temp;

	temp = phils;
	i = -1;
	while (temp[++i])
		if (sem_wait(temp[i]->finished))
			pthread_exit(0);
	sem_wait(temp[0]->init_data->for_print);
	sem_post(temp[0]->init_data->kill);
	pthread_exit(0);
}

int	ft_start_processes(t_phil_struct **phils)
{
	int			i;
	int			k;
	pthread_t	ph;
	pid_t		pid[200];

	k = phils[0]->init_data->num_phils;
	i = -1;
	if (k != 0)
		if (pthread_create(&ph, NULL, ft_count_eat, (void *)phils) != 0)
			return (0);
	while (++i < k)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (0);
		if (!pid[i])
			ft_eating(phils[i]);
	}
	i = -1;
	if (sem_wait(phils[0]->init_data->kill))
		return (0);
	while (phils[++i] != NULL)
		kill(pid[i], SIGKILL);
	return (1);
}
