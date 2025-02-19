/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:35:25 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/19 14:49:46 by ygorget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *nb, char *str)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		nbr = nbr * 10 + (nb[i] - '0');
		i++;
	}
	if (nb[i] != '\0' || nbr > 2147483647 || nbr < -2147483648 || nbr == 0)
	{
		if (nb[i] != '\0')
			return (print_error(NO_NUM));
		else if (nbr > 2147483647)
			return (print_error(TIME));
		else
			return (print_error(str));
	}
	return (nbr);
}

int	init_meal(t_data *data, char **tab)
{
	int	i;

	i = 0;
	if (tab[5])
	{
		data->max_meal = malloc(sizeof(int) * data->nbr_philo);
		if (!data->max_meal)
			return (-1);
		while (i < data->nbr_philo)
		{
			data->max_meal[i] = ft_atoi(tab[5], ERR_MEAL);
			if (data->nbr_philo < 1 || data->max_meal[0] < 1)
			{
				free (data->max_meal);
				return (-1);
			}
			i++;
		}
		data->meal = true;
	}
	else
		data->meal = false;
	return (0);
}

int	init_action(t_data *data, char **tab)
{
	data->death = 0;
	data->nbr_philo = ft_atoi(tab[1], ERR_PHILO);
	if (data->nbr_philo < 1)
		return (-1);
	data->died = ft_atoi(tab[2], ERR_DEATH);
	if (data->died <= 0)
		return (-1);
	data->eat = ft_atoi(tab[3], ERR_EAT) * 1000;
	if (data->eat <= 0)
		return (-1);
	data->sleep = ft_atoi(tab[4], ERR_SLEEP) * 1000;
	if (data->sleep <= 0)
		return (-1);
	return (0);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
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

int	init_data(t_data *data, char **tab)
{
	data->max_meal = NULL;
	data->philos = NULL;
	data->old_eating = NULL;
	data->old = NULL;
	data->mutex_fork = NULL;
	if (init_action(data, tab) == -1)
		return (-1);
	if (init_meal(data, tab) == -1)
		return (-1);
	data->philos = malloc(sizeof(pthread_t) * data->nbr_philo);
	if (!data->philos)
		return (free_malloc(data, MALLOC));
	data->old_eating = malloc(sizeof(int) * data->nbr_philo);
	if (!data->old_eating)
		return (free_malloc(data, MALLOC));
	data->old = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (!data->old)
		return (free_malloc(data, MALLOC));
	data->mutex_fork = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (!data->mutex_fork)
		return (free_malloc(data, MALLOC));
	init_mutex(data);
	gettimeofday(&data->start, NULL);
	return (0);
}
