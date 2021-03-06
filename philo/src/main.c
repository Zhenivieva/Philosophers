/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 00:02:36 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/06/29 00:02:40 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	one_phil(t_id_struct *init_data)
{
	pthread_mutex_lock(init_data->for_print);
	printf(YELLOW"%ld 1 has taken a left fork\n", get_current_time()
		- init_data->start);
	printf(YELLOW"%d 1 died\n", init_data->tt_die);
	pthread_mutex_unlock(init_data->for_print);
	return (2);
}

int	ft_parsing(char **argv, t_id_struct *init_data)
{
	if (!checkargs(argv))
		return (0);
	init_data->num_phils = ft_atoi(argv[1]);
	init_data->tt_die = ft_atoi(argv[2]);
	init_data->tt_eat = ft_atoi(argv[3]);
	init_data->tt_sleep = ft_atoi(argv[4]);
	init_data->end_flag = 0;
	init_data->to_stop = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(init_data->to_stop, NULL);
	if (argv[5])
		init_data->num_meals = ft_atoi(argv[5]);
	else
		init_data->num_meals = 1000000;
	init_data->for_print = malloc(sizeof(pthread_mutex_t));
	init_data->start = get_current_time();
	if (!init_data->for_print || pthread_mutex_init(init_data->for_print, NULL)
		|| init_data->tt_die < 1 || init_data->tt_eat < 1
		|| init_data->tt_sleep < 1 || init_data->num_meals < 0)
		return (0);
	if (init_data->num_phils == 1)
		return (one_phil(init_data));
	return (1);
}

int	ft_init_phil_struct(t_id_struct *init_data, t_phil_struct **phils)
{
	int	i;

	i = -1;
	while (++i < init_data->num_phils)
	{
		phils[i] = (t_phil_struct *)malloc(sizeof(t_phil_struct));
		if (!phils[i])
			return (0);
		phils[i]->id = i + 1;
		phils[i]->has_eaten = 0;
		phils[i]->finished = 0;
		phils[i]->left_ph = malloc(sizeof(pthread_mutex_t));
		if (!phils[i]->left_ph)
			return (0);
		phils[i]->init_data = init_data;
		phils[i]->t_must_die = get_current_time() + phils[i]->init_data->tt_die;
		if (i > 0 && phils[i]->left_ph)
			phils[i - 1]->right_ph = phils[i]->left_ph;
	}
	phils[i - 1]->right_ph = phils[0]->left_ph;
	phils[i] = NULL;
	return (1);
}

int	ft_start(char **argv)
{
	t_id_struct		*init_data;
	t_phil_struct	**phils;
	int				res;

	init_data = malloc(sizeof(t_id_struct));
	if (!init_data)
		return (0);
	res = ft_parsing(argv, init_data);
	if (!res)
		return (0);
	else if (res == 2)
		return (1);
	phils = (t_phil_struct **)malloc(sizeof(t_phil_struct *)
			* (init_data->num_phils + 1));
	if (!phils)
		return (0);
	if (!ft_init_phil_struct(init_data, phils) || !ft_start_threads(phils))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (-1);
	}
	if (!ft_start(argv))
		return (-1);
	return (0);
}
