/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:39:14 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/21 14:46:56 by ygorget          ###   ########.fr       */
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

void	print_action(t_data *data, char *str, int i)
{
	int	time;

	pthread_mutex_lock(&data->print);
	pthread_mutex_lock(&data->dead);
	time = times(data);
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
