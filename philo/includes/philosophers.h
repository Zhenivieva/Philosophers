/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:48:22 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/06/29 00:54:39 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define RED    "\x1b[31m"
# define GREEN    "\x1b[32m"
# define YELLOW    "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA    "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET    "\x1b[0m"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_id_struct
{
	int				num_phils;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				num_meals;
	pthread_mutex_t	*for_print;
	long			start;
	int				end_flag;
	pthread_mutex_t	*to_stop;
}					t_id_struct;

typedef struct s_phil_struct
{
	int				id;
	pthread_t		ph;
	int				has_eaten;
	int				finished;
	long			t_must_die;
	pthread_mutex_t	*right_ph;
	pthread_mutex_t	*left_ph;
	t_id_struct		*init_data;
}					t_phil_struct;

int		ft_isnumber(char *str);
int		ft_atoi(const char *str);
int		ft_start_threads(t_phil_struct **phils);
long	get_current_time(void);
int		message(t_phil_struct *phils, char *str);
int		checkargs(char **argv);
int		ft_to_sleep(t_id_struct *init_data, long n);

#endif
