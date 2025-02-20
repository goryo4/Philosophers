/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:20:12 by ygorget           #+#    #+#             */
/*   Updated: 2025/02/19 13:21:19 by ygorget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *str)
{
	printf("%s", str);
	return (-1);
}

int	free_malloc(t_data *data, char *str)
{
	free (data->max_meal);
	free (data->philos);
	free (data->old_eating);
	free (data->old);
	free (data->mutex_fork);
	printf("%s\n", str);
	return (-1);
}
