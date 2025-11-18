/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:43:06 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/14 19:32:59 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*monitoring_routine(void *arg)
{
	t_args	*vars;
	long	i;

	vars = (t_args *)arg;
	while (!(get_long(&vars->set_read_mutex, &vars->threads_ready)))
		usleep(1);
	i = 0;
	while (!(get_long(&vars->set_read_mutex, &vars->death_occured)))
	{
		pthread_mutex_lock(&vars->monitor_mutex);
		if (i == vars->philos_num)
			i = 0;
		vars->delta[i] = (get_time_in_ms() - vars->philos[i].last_meal);
		if (vars->delta[i] >= vars->time_to_die)
		{
			set_long(&vars->philo_mutex, &vars->death_occured, 1);
			pthread_mutex_lock(&vars->printf_mutex);
			printf(R "%lld %ld died"RESET "\n", 
				get_time_in_ms() - vars->start_time, vars->philos[i].id);
			pthread_mutex_unlock(&vars->printf_mutex);
		}
		pthread_mutex_unlock(&vars->monitor_mutex);
		i++;
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (!(get_long(&philo->vars->set_read_mutex, &philo->vars->threads_ready)))
		usleep(1);
	if (philo->parity == ODD)
		usleep((philo->vars->time_to_eat * 1000) / 2);
	while (!(get_long(&philo->vars->philo_mutex, &philo->vars->death_occured)))
	{
		if (!(get_long(&philo->vars->philo_mutex, &philo->vars->death_occured)))
			philo_eat(philo);
		if (!(get_long(&philo->vars->philo_mutex, &philo->vars->death_occured)))
			philo_sleep(philo);
		if (!(get_long(&philo->vars->philo_mutex, &philo->vars->death_occured)))
			philo_think(philo);
	}
	return (NULL);
}

void	philo_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);

	pthread_mutex_lock(&philo->vars->printf_mutex);
	printf(G"%lld %ld has taken a fork"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mutex);
	
	pthread_mutex_lock(&philo->left_fork->fork);

	pthread_mutex_lock(&philo->vars->printf_mutex);
	printf(G"%lld %ld has taken a fork"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mutex);

	pthread_mutex_lock(&philo->vars->printf_mutex);
	printf(B"%lld %ld is eating"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mutex);

	usleep(philo->vars->time_to_eat * 1000);
	pthread_mutex_lock(&philo->vars->philo_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->vars->philo_mutex);
	philo->meal_counter++;
	philo->full = 1;
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	philo_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->vars->printf_mutex);
	printf(Y"%lld %ld is sleeping"RESET"\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mutex);

	set_long(&philo->vars->philo_mutex, &philo->full, 0);
	usleep(philo->vars->time_to_sleep * 1000);
}

void	philo_think(t_philos *philo)
{
	pthread_mutex_lock(&philo->vars->printf_mutex);
	printf(G"%lld %ld is thinking"RESET"\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mutex);

	pthread_mutex_lock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

