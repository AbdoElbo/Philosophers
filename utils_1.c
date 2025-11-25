/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:08:04 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/25 14:15:29 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	start_mutexes(t_args *vars)
{
	long	i;

	i = 0;
	while (i < vars->philos_num)
	{
		pthread_mutex_init(&vars->forks[i].fork, NULL);
		i++;
	}
	pthread_mutex_init(&vars->philo_mtx, NULL);
	pthread_mutex_init(&vars->printf_mtx, NULL);
	pthread_mutex_init(&vars->monitor_mtx, NULL);
	pthread_mutex_init(&vars->set_read_mtx, NULL);
	pthread_mutex_init(&vars->time_mtx, NULL);
	vars->cleanup_flag = 1;
}

void	end_mutexes(t_args *vars)
{
	long	i;

	i = 0;
	while (i < vars->philos_num)
	{
		pthread_mutex_destroy(&vars->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&vars->printf_mtx);
	pthread_mutex_destroy(&vars->philo_mtx);
	pthread_mutex_destroy(&vars->monitor_mtx);
	pthread_mutex_destroy(&vars->set_read_mtx);
	pthread_mutex_destroy(&vars->time_mtx);
}

long long	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	cleanup(t_args *vars)
{
	if (!vars)
		return ;
	if (vars->cleanup_flag == 1)
		end_mutexes(vars);
	if (vars->philos)
		free(vars->philos);
	if (vars->forks)
		free(vars->forks);
	vars->philos = NULL;
	vars->forks = NULL;
}
