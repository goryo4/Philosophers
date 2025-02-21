/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:37:41 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/21 14:43:20 by ygorget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_thread *thread, int l_fork, int r_fork)
{
	if (thread->philo % 2 == 0)
	{
		pthread_mutex_lock(&thread->data->mutex_fork[l_fork]);
		if (philo_death(thread->data) == -1)
			return (unlock_one_fork(thread, l_fork));
		print_action(thread->data, FORK, thread->philo);
		pthread_mutex_lock(&thread->data->mutex_fork[r_fork]);
		if (philo_death(thread->data) == -1)
			return (unlock_two_fork(thread, l_fork, r_fork));
		print_action(thread->data, FORK, thread->philo);
	}
	else
	{
		pthread_mutex_lock(&thread->data->mutex_fork[r_fork]);
		if (philo_death(thread->data) == -1)
			return (unlock_one_fork(thread, r_fork));
		print_action(thread->data, FORK, thread->philo);
		pthread_mutex_lock(&thread->data->mutex_fork[l_fork]);
		if (philo_death(thread->data) == -1)
			return (unlock_two_fork(thread, r_fork, l_fork));
		print_action(thread->data, FORK, thread->philo);
	}
	return (0);
}

void	unlock_fork(t_thread *thread, int l_fork, int r_fork)
{
	if (thread->philo % 2 != 0)
		unlock_two_fork(thread, r_fork, l_fork);
	else
		unlock_two_fork(thread, l_fork, r_fork);
}

int	check_meal(t_thread *thread)
{
	int	i;

	pthread_mutex_lock(&thread->data->prot_meal);
	if (thread->meal == true)
	{
		i = 0;
		thread->data->max_meal[thread->philo - 1]--;
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
	}
	pthread_mutex_unlock(&thread->data->prot_meal);
	return (0);
}

int	eat(t_thread *thread, int l_fork, int r_fork)
{
	if (take_fork(thread, l_fork, r_fork) == -1)
		return (-1);
	if (philo_death(thread->data) == -1)
	{
		if (thread->philo % 2 != 0)
			unlock_two_fork(thread, r_fork, l_fork);
		else
			unlock_two_fork(thread, l_fork, r_fork);
		return (-1);
	}
	pthread_mutex_lock(&thread->data->old[thread->philo - 1]);
	thread->data->old_eating[thread->philo - 1] = times(thread->data);
	pthread_mutex_unlock(&thread->data->old[thread->philo - 1]);
	print_action(thread->data, EAT, thread->philo);
	if (ft_usleep(thread->data->eat, thread->data) == -1)
	{
		unlock_fork(thread, l_fork, r_fork);
		return (-1);
	}
	unlock_fork(thread, l_fork, r_fork);
	if (check_meal(thread) == -1)
		return (-1);
	return (1);
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
	if (wait_odd(thread) == -1)
		return (NULL);
	while (philo_death(thread->data) == 0)
	{
		if (eat(thread, l_fork, r_fork) == -1)
			break ;
		if (philo_death(thread->data) == -1)
			return (NULL);
		print_action(thread->data, SLEEP, thread->philo);
		if (ft_usleep(thread->data->sleep, thread->data) == -1)
			return (NULL);
		if (philo_death(thread->data) != -1)
			print_action(thread->data, THINK, thread->philo);
	}
	return (NULL);
}
