/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:37:26 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/21 14:47:32 by ygorget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_odd(t_thread *thread)
{
	if (thread->philo % 2 != 0)
	{
		if (ft_usleep(thread->data->eat + 1, thread->data) == -1)
			return (-1);
	}
	return (0);
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

int	get_time(void)
{
	struct timeval	act;

	gettimeofday(&act, NULL);
	return (act.tv_sec * 1000 + (act.tv_usec) / 1000);
}

int	ft_usleep(size_t milliseconds, t_data *data)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) * 1000 < milliseconds)
	{
		if (philo_death(data) == -1)
			return (-1);
		usleep(10);
	}
	return (0);
}
