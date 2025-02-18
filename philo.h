/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolan <yolan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:25:49 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/18 22:44:40 by yolan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
#include <stdbool.h> 

# define FORK "has taken a fork"
# define EAT " is eating"
# define SLEEP " is sleeping"
# define THINK " is thinking"
# define DEATH "died"

typedef struct s_data
{
	int				nbr_philo;
	int				death;
	int				*max_meal;
	bool			meal;
	float			eat;
	float			sleep;
	float			died;
	int				*old_eating;
	pthread_t		*philos;
	pthread_mutex_t prot_meal;
	pthread_mutex_t	time;
	pthread_mutex_t	dead;
	pthread_mutex_t	*old;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	print;
	struct timeval	start;
}	t_data;

typedef struct s_thread
{
	int		philo;
	int		max_philo;
	int		count;
	bool	meal;
	t_data	*data;
}	t_thread;

int		ft_atoi(char *nb);
int		init_data(t_data *data, char **tab);

int		unlock_one_fork(t_thread *thread, int fork);
int		unlock_two_fork(t_thread *thread, int l_fork, int r_fork);
int		take_fork(t_thread *thread, int l_fork, int r_fork);
int		eat(t_thread *thread, int l_fork, int r_fork);
void	*action(void *arg);

int		times(t_data *data);
void	print_action(t_data *data, char *str, int i);

int		death(t_data *data);
void	*check_death(void *arg);

#endif