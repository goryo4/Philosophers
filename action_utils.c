/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:39:14 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/19 17:27:35 by ygorget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	unlock_one_fork(t_thread *thread, int fork)
{
	pthread_mutex_unlock(&thread->data->mutex_fork[fork]);
	return (-1);
}

int	unlock_two_fork(t_thread *thread, int fork1, int fork2)
{
	pthread_mutex_unlock(&thread->data->mutex_fork[fork1]);
	pthread_mutex_unlock(&thread->data->mutex_fork[fork2]);
	return (-1);
}

int	times(t_data *data)
{
	struct timeval	act;
	int				time;

	gettimeofday(&act, NULL);
	pthread_mutex_lock(&data->time);
	time = ((act.tv_sec - data->start.tv_sec) * 1000000
			+ (act.tv_usec - data->start.tv_usec)) / 1000;
	pthread_mutex_unlock(&data->time);
	return (time);
}

void	print_action(t_data *data, char *str, int i)
{
	int	time;

	pthread_mutex_lock(&data->print);
	time = times(data);
	pthread_mutex_lock(&data->dead);
	if (data->death != -1)
		printf("%d %d %s", time, i, str);
	pthread_mutex_unlock(&data->dead);
	pthread_mutex_unlock(&data->print);
}

void	*one_philo(t_thread *thread)
{
	print_action(thread->data, FORK, thread->philo);
	return (NULL);
}
