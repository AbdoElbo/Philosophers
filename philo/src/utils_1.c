/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:08:04 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/12/10 17:54:02 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	start_mutexes(t_args *vars)
{
	long	i;

	vars->stat_print = 0;
	vars->stat_set_read = 0;
	vars->stat_time = 0;
	i = 0;
	while (i < vars->philos_num)
	{
		if (pthread_mutex_init(&vars->forks[i].fork, NULL))
			return (0);
		vars->forks[i].ok = 1;
		i++;
	}
	if (pthread_mutex_init(&vars->printf_mtx, NULL))
		return (0);
	vars->stat_print = 1;
	if (pthread_mutex_init(&vars->set_read_mtx, NULL))
		return (0);
	vars->stat_set_read = 1;
	if (pthread_mutex_init(&vars->time_mtx, NULL))
		return (0);
	vars->stat_time = 1;
	return (1);
}

void	end_mutexes(t_args *vars)
{
	long	i;

	i = 0;
	while (i < vars->philos_num)
	{
		if (vars->forks[i].ok == 1)
			pthread_mutex_destroy(&vars->forks[i].fork);
		i++;
	}
	if (vars->stat_print)
		pthread_mutex_destroy(&vars->printf_mtx);
	if (vars->stat_set_read)
		pthread_mutex_destroy(&vars->set_read_mtx);
	if (vars->stat_time)
		pthread_mutex_destroy(&vars->time_mtx);
}

/// @brief returns current time in millieseconds
long long	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	cleanup(t_args *vars)
{
	int	i;

	if (!vars)
		return ;
	i = 0;
	end_mutexes(vars);
	if (vars->philos)
		free(vars->philos);
	if (vars->forks)
		free(vars->forks);
	vars->philos = NULL;
	vars->forks = NULL;
}

void	print_status(t_philos *philo, char *status, const char *color)
{
	long long	current_time;

	if (get_long(&philo->vars->set_read_mtx, &philo->vars->sim_end))
		return ;
	pthread_mutex_lock(&philo->vars->printf_mtx);
	if (!(get_long(&philo->vars->set_read_mtx, &philo->vars->sim_end)))
	{
		current_time = get_time_in_ms() - philo->vars->start_time;
		if (philo->vars->color == true)
		{
			printf("%s%lld %ld %s%s\n", color, current_time,
				philo->id + 1, status, RESET);
		}
		else
			printf("%lld %ld %s\n", current_time, philo->id + 1, status);
	}
	pthread_mutex_unlock(&philo->vars->printf_mtx);
}
