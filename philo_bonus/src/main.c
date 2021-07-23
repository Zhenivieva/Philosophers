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

int	ft_init_sems(t_id_struct *init_data)
{
	init_data->for_print = malloc(sizeof(sem_t));
	init_data->fork = malloc(sizeof(sem_t));
	init_data->kill = malloc(sizeof(sem_t));
	if (!init_data->for_print || !init_data->fork || !init_data->kill)
		return (0);
	sem_unlink("/for_print");
	sem_unlink("/fork");
	sem_unlink("/kill");
	init_data->for_print = sem_open("/for_print", O_CREAT, 0666, 1);
	init_data->fork = sem_open("/fork", O_CREAT, 0666, init_data->num_phils);
	init_data->kill = sem_open("/kill", O_CREAT, 0666, 1);
	if (init_data->for_print == SEM_FAILED || init_data->fork == SEM_FAILED \
		|| init_data->kill == SEM_FAILED || sem_wait(init_data->kill))
		return (0);
	if (init_data->num_phils == 1)
		return (ft_one_phil(init_data));
	return (1);
}

int	ft_parsing(char **argv, t_id_struct *init_data)
{
	if (!ft_checkargs(argv))
		return (0);
	init_data->num_phils = ft_atoi(argv[1]);
	init_data->tt_die = ft_atoi(argv[2]);
	init_data->tt_eat = ft_atoi(argv[3]);
	init_data->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		init_data->num_meals = ft_atoi(argv[5]);
	else
		init_data->num_meals = 0;
	init_data->start = ft_get_current_time();
	if (init_data->tt_die < 1 || init_data->tt_eat < 1
		|| init_data->tt_sleep < 1 || init_data->num_meals < 0)
		return (0);
	return (ft_init_sems(init_data));
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
		phils[i]->name = ft_itoa(phils[i]->id);
		if (!phils[i]->name)
			return (0);
		phils[i]->has_eaten = 0;
		phils[i]->finished = malloc(sizeof(sem_t));
		sem_unlink(phils[i]->name);
		phils[i]->finished = sem_open(phils[i]->name, O_CREAT, 0666, 1);
		phils[i]->init_data = init_data;
		phils[i]->t_must_die = ft_get_current_time()
			+ phils[i]->init_data->tt_die;
		if (!phils[i]->finished || sem_wait(phils[i]->finished))
			return (0);
	}
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
	if (!ft_init_phil_struct(init_data, phils) || !ft_start_processes(phils))
		return (0);
	ft_sem_closes(phils);
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
