/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:35:25 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/18 16:44:46 by ygorget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *nb)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		nbr = nbr * 10 + (nb[i] - '0');
		i++;
	}
	if (nbr == 0)
		exit (1);
	return (nbr);
}

void	init_data(t_data *data, char **tab)
{
	int	i;

	i = 0;
	gettimeofday(&data->start, NULL);
	data->death = 0;
	data->nbr_philo = ft_atoi(tab[1]);
	data->died = ft_atoi(tab[2]);
	data->eat = ft_atoi(tab[3]) * 1000;
	data->sleep = ft_atoi(tab[4]) * 1000;
    if (tab[5])
	{
		data->max_meal = malloc(sizeof(int) * data->nbr_philo);
		while (i < data->nbr_philo)
		{
	    	data->max_meal[i] = ft_atoi(tab[5]);
			i++;
		}
		data->meal = true;
		i = 0;
	}
    else
		data->meal = false;
	data->philos = malloc(sizeof(pthread_t) * data->nbr_philo);
	data->old_eating = malloc(sizeof(int) * data->nbr_philo);
	data->old = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	data->mutex_fork = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->old[i], NULL);
		pthread_mutex_init(&data->mutex_fork[i], NULL);
		data->old_eating[i] = 0;
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->time, NULL);
	pthread_mutex_init(&data->prot_meal, NULL);
}
