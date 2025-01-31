/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolan <yolan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:41:54 by yolan             #+#    #+#             */
/*   Updated: 2025/01/13 16:52:15 by yolan            ###   ########.fr       */
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

typedef struct data_s
{
    int *fork;
    int philo;
    float eat;
    float sleep;
    float died;
    float mili_s;
    int i;
    int *old_eating;
    pthread_t *philos;
    struct timeval start;
    struct timeval act;
    pthread_mutex_t *mutex_fork;
} data_t;

#endif