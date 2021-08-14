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
# include <semaphore.h>
# include <signal.h>

typedef struct s_id_struct
{
	int			num_phils;
	int			tt_die;
	int			tt_eat;
	int			tt_sleep;
	int			num_meals;
	long		start;
	sem_t		*for_print;
	sem_t		*fork;
	sem_t		*kill;
}				t_id_struct;

typedef struct s_phil_struct
{
	int			id;
	pthread_t	ph;
	char		*name;
	int			has_eaten;
	sem_t		*finished;
	long		t_must_die;
	t_id_struct	*init_data;
}				t_phil_struct;

int		ft_start_processes(t_phil_struct **phils);
void	ft_sem_unlink(t_phil_struct **phils);
int		ft_checkargs(char **argv);
int		ft_isnumber(char *str);
int		ft_atoi(const char *str);
long	ft_get_current_time(void);
int		ft_message(t_phil_struct *phils, char *str);
char	*ft_filldest(char *dest, int n, size_t len);
size_t	ft_retlen(int n);
char	*ft_itoa(int n);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_one_phil(t_id_struct *init_data);
int		ft_to_sleep(t_id_struct *init_data, long n);

#endif
