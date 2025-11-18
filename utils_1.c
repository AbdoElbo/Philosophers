/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:08:04 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/14 15:11:26 by aelbouaz         ###   ########.fr       */
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
	pthread_mutex_init(&vars->philo_mutex, NULL);
	pthread_mutex_init(&vars->printf_mutex, NULL);
	pthread_mutex_init(&vars->monitor_mutex, NULL);
	pthread_mutex_init(&vars->set_read_mutex, NULL);
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
	pthread_mutex_destroy(&vars->printf_mutex);
	pthread_mutex_destroy(&vars->philo_mutex);
	pthread_mutex_destroy(&vars->monitor_mutex);
	pthread_mutex_destroy(&vars->set_read_mutex);
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
	if (vars->delta)
		free(vars->delta);
	vars->delta = NULL;
	vars->philos = NULL;
	vars->forks = NULL;
}

long long	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
/// @brief safely return the value of dst
long    get_long(pthread_mutex_t *mutex ,long *dst)
{
	long	number;

	pthread_mutex_lock(mutex);
	number = *dst;
	pthread_mutex_unlock(mutex);
	return (number);
}
/// @brief safely set "dst" to "Updated" 
void    set_long(pthread_mutex_t *mutex , long *dst, long updated)
{
	pthread_mutex_lock(mutex);
	*dst = updated;
	pthread_mutex_unlock(mutex);
}
