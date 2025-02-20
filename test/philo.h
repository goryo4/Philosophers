/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:25:49 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/20 12:04:12 by ygorget          ###   ########.fr       */
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
# include <stdbool.h> 

# define ARG "it must have 5 or 6 arguments\n"
# define FORK "has taken a fork\n"
# define EAT " is eating\n"
# define SLEEP " is sleeping\n"
# define THINK " is thinking\n"
# define DEATH "died\n"
# define ERR_PHILO "there is not even a philosopher\n"
# define ERR_DEATH "death is immediate\n"
# define ERR_EAT "it's too fast to eat\n"
# define ERR_SLEEP "it's too fast to sleep\n"
# define ERR_MEAL "there is not even a meal\n"
# define NO_NUM "the argument it's not numeric argument\n"
# define MALLOC "memory allocation failed\n"
# define TIME "it's too long\n"

typedef struct s_data
{
	int				nbr_philo;
	int				death;
	int				*max_meal;
	bool			meal;
	long			eat;
	long			sleep;
	long			died;
	int				*old_eating;
	pthread_t		*philos;
	pthread_mutex_t	prot_meal;
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
	pthread_mutex_t	mutex_fork[2];
}	t_thread;

int		print_error(char *str);
long	ft_atoi(char *nb, char *str);
int		init_data(t_data *data, char **tab);

int		unlock_one_fork(t_thread *thread, int fork);
int		unlock_two_fork(t_thread *thread, int l_fork, int r_fork);
int		take_fork(t_thread *thread, int l_fork, int r_fork);
int		eat(t_thread *thread, int l_fork, int r_fork);
void	*action(void *arg);

int		unlock_one_fork(t_thread *thread, int fork);
int		unlock_two_fork(t_thread *thread, int fork1, int fork2);
int		times(t_data *data);
void	print_action(t_data *data, char *str, int i);
void	*one_philo(t_thread *thread);

int		philo_death(t_data *data);
void	*check_death(void *arg);

int		print_error(char *str);
int		free_malloc(t_data *data, char *str);

#endif