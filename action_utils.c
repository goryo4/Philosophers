/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:39:14 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/18 17:02:48 by ygorget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
    int time;
    
	pthread_mutex_lock(&data->print);
    time = times(data);
	pthread_mutex_lock(&data->dead);
	if (data->death != -1)
		printf("%d ms %d %s\n", time, i, str);
	pthread_mutex_unlock(&data->dead);
	pthread_mutex_unlock(&data->print);
}
