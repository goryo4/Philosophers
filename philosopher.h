/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:41:54 by yolan             #+#    #+#             */
/*   Updated: 2025/01/31 15:29:41 by ygorget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

typedef struct s_thread
{
	int	philo;
	int old_eating;
}	t_thread;

typedef struct data_s
{
    int nbr_philo;
    float eat;
    float sleep;
    float died;
    pthread_t *philos;
    pthread_mutex_t *mutex_fork;
	t_thread	*thread_data;
    struct timeval start;
    struct timeval act;
} data_t;

#endif