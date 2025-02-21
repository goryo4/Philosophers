/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:25:38 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/21 14:36:12 by ygorget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	{
		print_error(ARG);
		return (0);
	}
	if (init_data(&data, argv) == 0)
	{
		thread = malloc(sizeof(t_thread) * data.nbr_philo);
		start_thread(data, thread);
		ft_free(&data, thread);
	}
	return (0);
}
