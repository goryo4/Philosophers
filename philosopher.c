/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolan <yolan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:21:23 by yolan             #+#    #+#             */
/*   Updated: 2025/01/13 17:39:43 by yolan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int    times(struct timeval start, struct timeval act)
{
    return (((act.tv_sec - start.tv_sec) * 1000000 + (act.tv_usec - start.tv_usec)) / 1000);
}
void eat(data_t *phi, int nbr, int r_fork, int l_fork)
{
    if (phi->i % 2 != 0)
    {
        pthread_mutex_lock(&phi->mutex_fork[r_fork]);
        gettimeofday(&phi->act, NULL);
        printf("%d ms | philosopher %d | take rigth fork %d\n", times(phi->start, phi->act), phi->i, r_fork);
        pthread_mutex_lock(&phi->mutex_fork[l_fork]);
        gettimeofday(&phi->act, NULL);
        printf("%d ms | philosopher %d | take left fork %d\n", times(phi->start, phi->act), phi->i, l_fork);
    }
    else
    {
        pthread_mutex_lock(&phi->mutex_fork[l_fork]);
        gettimeofday(&phi->act, NULL);
        printf("%d ms | philosopher %d | take left : %d\n", times(phi->start, phi->act), phi->i, l_fork);
        pthread_mutex_lock(&phi->mutex_fork[r_fork]);
        gettimeofday(&phi->act, NULL);
        printf("%d ms | philosopher %d | take rigth : %d\n", times(phi->start, phi->act), phi->i, r_fork);
    }
    gettimeofday(&phi->act, NULL);
    if (times(phi->start, phi->act) - phi->old_eating[phi->i - 1] > phi->died)
    {
        printf("%d ms | philosopher %d | dead\n", times(phi->start, phi->act), phi->i);
        exit (0);
    }
    printf("%d ms | philosopher %d | eat\n", times(phi->start, phi->act), phi->i);
    phi->old_eating[phi->i - 1] = times(phi->start, phi->act);
    usleep (phi->eat);
    pthread_mutex_unlock(&phi->mutex_fork[l_fork]);
    pthread_mutex_unlock(&phi->mutex_fork[r_fork]);
}

void *action(void *arg)
{
    data_t *phi;
    int l_fork;
    int r_fork;

    phi = (data_t *)arg;
    while (1)
    {
        l_fork = (phi->i - 1 + phi->philo) % phi->philo;
        r_fork = phi->i % phi->philo;
        eat(phi, phi->i, r_fork, l_fork);
        gettimeofday(&phi->act, NULL);
        printf("%d ms | philosopher %d | sleeping\n", times(phi->start, phi->act), phi->i);
        usleep(phi->sleep);
        gettimeofday(&phi->act, NULL);
        printf("%d ms | philosopher %d | thinking\n", times(phi->start, phi->act), phi->i);
    }
}

int ft_atoi(char *nb)
{
    int i;
    int nbr;

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

int main(int argc, char **argv)
{
    data_t data;
    data_t *thread_data;
    int i;

    data.i = 0;
    i = 0;
    if (argc != 5)
        return (0);
    gettimeofday(&data.start, NULL);
    data.philo = ft_atoi(argv[1]);
    data.eat = ft_atoi(argv[2]) * 1000;
    data.sleep = ft_atoi(argv[3]) * 1000;
    data.died = ft_atoi(argv[4]) ;
    printf("| TIME | PHILOSOPHERS | ACTION |\n");
    data.philos = malloc(sizeof(pthread_t) * data.philo);
    data.fork = malloc(sizeof(int) * data.philo);
    data.old_eating = malloc(sizeof(int) * data.philo);
    while (i < data.philo)
    {
        data.old_eating[i] = 0;
        i++;
    }
    data.mutex_fork = malloc(sizeof(pthread_mutex_t) * data.philo);
    i = 0;
    while (i < data.philo)
    {
        pthread_mutex_init(&data.mutex_fork[i], NULL);
        i++;
    }
    while (data.i < data.philo)
    {
        thread_data = malloc(sizeof(data_t));
        *thread_data = data;
        thread_data->i = data.i + 1;
        pthread_create(&data.philos[data.i], NULL, action, thread_data);
        data.i++;
    }
    data.i = 0;
    while (data.i < data.philo)
    {
        pthread_join(data.philos[data.i], NULL);
        data.i++;
    }
    pthread_mutex_destroy(data.mutex_fork);
    return (0);
}
