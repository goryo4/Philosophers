/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:21:23 by yolan             #+#    #+#             */
/*   Updated: 2025/01/31 15:33:43 by ygorget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	times(data_t *phi)
{
	gettimeofday(&phi->act, NULL);
	return (((phi->act.tv_sec - phi->start.tv_sec) * 1000000 + (phi->act.tv_usec - phi->start.tv_usec)) / 1000);
}

void	death(data_t *phi)
{
	int	i;

	i = 0;
	free (phi->philos);
	free (phi->thread_data);
	pthread_mutex_destroy(phi->mutex_fork);
}

void	eat(data_t *phi, int nbr, int r_fork, int l_fork)
{
	if (phi->thread_data->philo % 2 != 0)
	{
		pthread_mutex_lock(&phi->mutex_fork[r_fork]);
		printf("%d %d has taken a fork\n", times(phi), phi->thread_data->philo);
		pthread_mutex_lock(&phi->mutex_fork[l_fork]);
		printf("%d %d has taken a fork\n", times(phi), phi->thread_data->philo);
	}
	else
	{
		pthread_mutex_lock(&phi->mutex_fork[l_fork]);
		printf("%d %d has taken a fork\n", times(phi), phi->thread_data->philo);
		pthread_mutex_lock(&phi->mutex_fork[r_fork]);
		printf("%d %d has taken a fork\n", times(phi), phi->thread_data->philo);
	}
	if (times(phi) - phi->thread_data->old_eating[&phi->thread_data->philo - 1] > phi->died)
	{
		printf("%d %d died\n", times(phi), phi->thread_data->philo);
		death(phi);
		exit (0);
	}
	printf("%d %d is eating\n", times(phi), phi->thread_data->philo);
	phi->thread_data->old_eating[&phi->thread_data->philo - 1] = times(phi);
	usleep (phi->eat);
	pthread_mutex_unlock(&phi->mutex_fork[l_fork]);
	pthread_mutex_unlock(&phi->mutex_fork[r_fork]);
}

void	*action(void *arg)
{
	data_t	*phi;
	int		l_fork;
	int		r_fork;

	phi = (data_t *)arg;
	printf("philo = %d\n", phi->thread_data->philo);
	while (1)
	{
		l_fork = (phi->thread_data->philo - 1 + phi->nbr_philo) % phi->nbr_philo;
		r_fork = phi->thread_data->philo % phi->nbr_philo;
		eat(phi, phi->thread_data->philo, r_fork, l_fork);
		printf("%d %d is sleeping\n", times(phi), phi->thread_data->philo);
		usleep(phi->sleep);
		printf("%d %d is thinking\n", times(phi), phi->thread_data->philo);
	}
}

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

void	init_data(data_t *data, char **tab)
{
	int	i;

	i = 0;
	gettimeofday(&data->start, NULL);
	data->nbr_philo = ft_atoi(tab[1]);
	data->eat = ft_atoi(tab[3]) * 1000;
	data->sleep = ft_atoi(tab[4]) * 1000;
	data->died = ft_atoi(tab[2]);
	data->philos = malloc(sizeof(pthread_t) * data->nbr_philo);
	//data->old_eating = malloc(sizeof(int) * data->nbr_philo);
	// while (i < data->philo)
	// {
	// 	data->old_eating[i] = 0;
	// 	i++;
	// }
	data->mutex_fork = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->mutex_fork[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	data_t	data;
	int		i;
	
	i = 0;
	if (argc != 5)
		return (0);
	init_data(&data, argv);
	while (i < data.nbr_philo)
	{
		data.thread_data = malloc(sizeof(t_thread));
		//*thread_data = data;
		data.thread_data->old_eating = 0;
		data.thread_data->philo = i + 1;
		printf("before philo = %d\n", data.thread_data->philo);
		pthread_create(&data.philos[i], NULL, action, &data);
		i++;
	}
	i = 0;
	while (i < data.nbr_philo)
	{
		pthread_join(data.philos[i], NULL);
		i++;
	}
	return (0);
}
