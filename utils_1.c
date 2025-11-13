/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:08:04 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/13 18:48:57 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	start_mutexes(t_args *vars)
{
	long	i;

	i = 0;
	while (i < vars->philos_num)
	{
		pthread_mutex_init(&vars->printf_mutex[i], NULL);
		pthread_mutex_init(&vars->forks[i].fork, NULL);
		i++;
	}
	pthread_mutex_init(vars->mutex, NULL);
	pthread_mutex_init(&vars->monitor_mutex, NULL);
}

void	end_mutexes(t_args *vars)
{
	long	i;

	i = 0;
	while (i < vars->philos_num)
	{
		pthread_mutex_destroy(&vars->printf_mutex[i]);
		pthread_mutex_destroy(&vars->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(vars->mutex);
	pthread_mutex_destroy(&vars->monitor_mutex);
}

void	cleanup(t_args *vars, int flag)
{
	if (!vars)
		return ;
	if (flag == 1)
		end_mutexes(vars);
	if (vars->philos)
		free(vars->philos);
	if (vars->forks)
		free(vars->forks);
	if (vars->printf_mutex)
		free(vars->printf_mutex);
	vars->printf_mutex = NULL;
	vars->philos = NULL;
	vars->forks = NULL;
}
