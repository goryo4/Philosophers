/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolan <yolan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:37:41 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/18 23:29:11 by yolan            ###   ########.fr       */
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

int	take_fork(t_thread *thread, int l_fork, int r_fork)
{
	if (thread->philo % 2 != 0)
	{
		pthread_mutex_lock(&thread->data->mutex_fork[r_fork]);
		if (death(thread->data) == -1)
			return (unlock_one_fork(thread, r_fork));
		print_action(thread->data, FORK, thread->philo);
		pthread_mutex_lock(&thread->data->mutex_fork[l_fork]);
		if (death(thread->data) == -1)
			return (unlock_two_fork(thread, r_fork, l_fork));
		print_action(thread->data, FORK, thread->philo);
	}
	else if (thread->philo % 2 == 0)
	{
		pthread_mutex_lock(&thread->data->mutex_fork[l_fork]);
		if (death(thread->data) == -1)
			return (unlock_one_fork(thread, l_fork));
		print_action(thread->data, FORK, thread->philo);
		pthread_mutex_lock(&thread->data->mutex_fork[r_fork]);
		if (death(thread->data) == -1)
			return (unlock_two_fork(thread, l_fork, r_fork));
		print_action(thread->data, FORK, thread->philo);
	}
	return (0);
}

int	eat(t_thread *thread, int l_fork, int r_fork)
{
	if (take_fork(thread, l_fork, r_fork) == -1)
		return (-1);
	if (death(thread->data) == -1)
	{
		if (thread->philo % 2 != 0)
			unlock_two_fork(thread, r_fork, l_fork);
		if (thread->philo % 2 == 0)
			unlock_two_fork(thread, l_fork, r_fork);
		return (-1);
	}
	print_action(thread->data, EAT, thread->philo);
	pthread_mutex_lock(&thread->data->old[thread->philo - 1]);
	thread->data->old_eating[thread->philo - 1] = times(thread->data);
	pthread_mutex_unlock(&thread->data->old[thread->philo - 1]);
	usleep(thread->data->eat);
	if (thread->philo % 2 != 0)
		unlock_two_fork(thread, r_fork, l_fork);
	if (thread->philo % 2 == 0)
		unlock_two_fork(thread, l_fork, r_fork);
	return (1);
}

int		check_meal(t_thread *thread)
{
	int	i;
	
	pthread_mutex_lock(&thread->data->prot_meal);
	if (thread->meal == true)
	{
		i = 0;
		while (i < thread->data->nbr_philo)
		{
			if (thread->data->max_meal[i] > 0)
				break ;
			i++;
		}
		if (i == thread->data->nbr_philo)
		{
			pthread_mutex_unlock(&thread->data->prot_meal);
			return (-1);
		}
		thread->data->max_meal[thread->philo - 1]--;
	}
	pthread_mutex_unlock(&thread->data->prot_meal);
	return (0);
}

void	*one_philo(t_thread *thread)
{
	print_action(thread->data, FORK, thread->philo);
	return (NULL);
}

void	*action(void *arg)
{
	t_thread	*thread;
	int			l_fork;
	int			r_fork;

	thread = (t_thread *)arg;
	l_fork = (thread->philo - 1 + thread->max_philo) % thread->max_philo;
	r_fork = thread->philo % thread->max_philo;
	if (thread->max_philo == 1)
		return (one_philo(thread));
	while (death(thread->data) == 0)
	{
		if (eat(thread, l_fork, r_fork) == -1)
			break ;
		if (check_meal(thread) == -1)
			break ;
		if (death(thread->data) != -1)
		{
			print_action(thread->data, SLEEP, thread->philo);
			usleep(thread->data->sleep);
		}
		if (death(thread->data) != -1)
			print_action(thread->data, THINK, thread->philo);
	}
	return (NULL);
}
