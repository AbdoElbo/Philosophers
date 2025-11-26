/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:02:30 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/26 13:58:31 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	philo_eat(t_philos *philo)
{
	int	first;
	int	second;

	first = philo->right_fork->fork_id;
	second = philo->left_fork->fork_id;
	if (first < second)
		lock_right_fork_first(philo);
	else
		lock_left_fork_first(philo);

	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(B"%lld %ld is eating"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mtx);

	set_long_long(&philo->vars->time_mtx, &philo->last_meal,
		get_time_in_ms() + philo->vars->time_to_eat);
	usleep(philo->vars->time_to_eat * 1000);
	pthread_mutex_lock(&philo->vars->philo_mtx);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->vars->philo_mtx);
	set_long_long(&philo->vars->time_mtx, &philo->last_meal, get_time_in_ms());
 //
	if (get_long(&philo->vars->philo_mtx, &philo->meal_counter) == philo->vars->meals_to_eat)
	{
		pthread_mutex_lock(&philo->vars->printf_mtx);
		printf(M"%lld %ld has eaten LAST meal "RESET "\n",
			get_time_in_ms() - philo->vars->start_time, philo->id);
		pthread_mutex_unlock(&philo->vars->printf_mtx);
	}
 // this is for testing max meals
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	lock_right_fork_first(t_philos *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(G"%lld %ld has taken a fork"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(G"%lld %ld has taken a fork"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
}

void	lock_left_fork_first(t_philos *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(G"%lld %ld has taken a fork"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
	pthread_mutex_lock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(G"%lld %ld has taken a fork"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
}

void	philo_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(Y"%lld %ld is sleeping"RESET"\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
	usleep(philo->vars->time_to_sleep * 1000);
}

void	philo_think(t_philos *philo)
{
	int	first;
	int	second;

	first = philo->right_fork->fork_id;
	second = philo->left_fork->fork_id;
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(G"%lld %ld is thinking"RESET"\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
	if (first < second)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		pthread_mutex_lock(&philo->left_fork->fork);
		pthread_mutex_unlock(&philo->left_fork->fork);
		pthread_mutex_unlock(&philo->right_fork->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		pthread_mutex_lock(&philo->right_fork->fork);
		pthread_mutex_unlock(&philo->right_fork->fork);
		pthread_mutex_unlock(&philo->left_fork->fork);
	}
}

