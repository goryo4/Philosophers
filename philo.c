/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolan <yolan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:25:38 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/18 23:29:01 by yolan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death(t_data *data)
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

void	*check_death(void *arg)
{
	int		i;
	int		time_since_last_eating;
	t_data	*data;

	data = (t_data *)arg;
	if (data->nbr_philo == 1)
	{
		usleep(data->died * 1000);
		print_action(data, DEATH, 1);
		return (NULL);
	}
	while (death(data) == 0)
	{
		if (meal(data) == -1)
			break ;
		usleep(10);
		i = -1;
		while (++i < data->nbr_philo)
		{
			pthread_mutex_lock(&data->old[i]);
			time_since_last_eating = times(data) - data->old_eating[i];
			pthread_mutex_unlock(&data->old[i]);
			if (time_since_last_eating >= data->died)
			{
				print_action(data, DEATH, i + 1);
				pthread_mutex_lock(&data->dead);
				data->death = -1;
				pthread_mutex_unlock(&data->dead);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	ft_free(t_data *data, t_thread *thread)
{
	int	i;

	i = 0;
	free(data->philos);
	free(data->old_eating);
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->old[i]);
		pthread_mutex_destroy(&data->mutex_fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->time);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->print);
	free (data->old);
	free (data->mutex_fork);
	free (thread);
}

void	start_thread(t_data data, t_thread *thread)
{
	pthread_t	monitoring;
	int			i;

	i = 0;
	pthread_create(&monitoring, NULL, check_death, &data);
	while (i < data.nbr_philo)
	{
		thread[i].data = &data;
		thread[i].philo = i + 1;
		thread[i].max_philo = data.nbr_philo;
		if (data.meal == true)
			thread[i].meal = true;
		else
			thread[i].meal = false;
		pthread_create(&data.philos[i], NULL, action, &thread[i]);
		i++;
	}
	i = 0;
	while (i < data.nbr_philo)
	{
		if (i == 0)
			pthread_join(monitoring, NULL);
		pthread_join(data.philos[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_thread	*thread;

	if (argc < 5 || argc > 6)
		return (0);
	if (init_data(&data, argv) == 0)
	{
		thread = malloc(sizeof(t_thread) * data.nbr_philo);
		start_thread(data, thread);
		ft_free(&data, thread);
	}
	return (0);
}
