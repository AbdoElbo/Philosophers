/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:08:04 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/10 16:43:20 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	start_mutexes(t_args *vars)
{
	long	i;

	i = 0;
	pthread_mutex_init(&vars->printf_mutex, NULL);
	while (i < vars->philos_num)
	{
		pthread_mutex_init(&vars->forks[i].fork, NULL);
		i++;
	}
}

void	end_mutexes(t_args *vars)
{
	long	i;

	i = 0;
	pthread_mutex_destroy(&vars->printf_mutex);
	while (i < vars->philos_num)
	{
		pthread_mutex_destroy(&vars->forks[i].fork);
		i++;
	}
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
	if (vars->monitoring)
		free(vars->monitoring);
	vars->philos = NULL;
	vars->monitoring = NULL;
	vars->forks = NULL;
}
