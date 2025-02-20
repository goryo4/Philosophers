/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:38:26 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/20 12:02:47 by ygorget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_death(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	if (data->death == -1)
	{
		pthread_mutex_unlock(&data->dead);
		return (-1);
	}
	pthread_mutex_unlock(&data->dead);
	return (0);
}

int	meal(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->prot_meal);
	if (data->meal == true)
	{
		while (i < data->nbr_philo)
		{
			if (data->max_meal[i] > 0)
				break ;
			i++;
		}
		if (i == data->nbr_philo)
		{
			pthread_mutex_unlock(&data->prot_meal);
			return (-1);
		}
	}
	pthread_mutex_unlock(&data->prot_meal);
	return (0);
}

int	death(t_data *data, int i)
{
	int		time;

	pthread_mutex_lock(&data->old[i]);
	time = times(data) - data->old_eating[i];
	pthread_mutex_unlock(&data->old[i]);
	if (time > data->died)
	{
		print_action(data, DEATH, i + 1);
		pthread_mutex_lock(&data->dead);
		data->death = -1;
		pthread_mutex_unlock(&data->dead);
		return (0);
	}
	return (1);
}

void	*check_death(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	if (data->nbr_philo == 1)
	{
		usleep(data->died * 1000);
		print_action(data, DEATH, 1);
		return (NULL);
	}
	while (philo_death(data) == 0)
	{
		if (meal(data) == -1)
			break ;
		i = -1;
		while (++i < data->nbr_philo)
		{
			if (!death(data, i))
				return (NULL);
		}
	}
	return (NULL);
}
