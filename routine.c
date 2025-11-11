/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:43:06 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/11 19:28:25 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->state == EATING)
		philo_eat(philo);
	else
	{
		philo_sleep(philo, 10);
		pthread_mutex_lock(&philo->vars->printf_mutex[philo->id]);
		printf("%ld is IDLE\n", philo->id);
		pthread_mutex_unlock(&philo->vars->printf_mutex[philo->id]);
	}
	while (!philo->vars->death_occured)
	{
		philo->vars->delta = get_time_in_ms() - philo->vars->start_time;
		if (philo->vars->delta > 100)
		{
			philo_eat(philo);
			philo_sleep(philo, philo->vars->time_to_sleep);
			philo_think(philo);
			philo->vars->delta = 0;
		}
	}
}

/// @brief
/// @param philo
void	philo_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->left_fork->fork);
	usleep(philo->vars->time_to_eat);
	pthread_mutex_lock(&philo->vars->mutex[philo->id]);
	pthread_mutex_lock(&philo->vars->printf_mutex[philo->id]);
	printf("%lld ", get_time_in_ms() - philo->vars->start_time);
	printf("%ld is eating\n", philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mutex[philo->id]);
	philo->state = EATING;
	philo->full = 1;
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->vars->mutex[philo->id]);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

/// @brief
/// @param philo
void	philo_sleep(t_philos *philo, long time)
{
	pthread_mutex_lock(&philo->vars->mutex[philo->id]);
	philo->state = SLEEPING;
	pthread_mutex_lock(&philo->vars->printf_mutex[philo->id]);
	printf("%lld ", get_time_in_ms() - philo->vars->start_time);
	printf("%ld is sleeping\n", philo->id);
	usleep(time);
	pthread_mutex_unlock(&philo->vars->printf_mutex[philo->id]);
	pthread_mutex_unlock(&philo->vars->mutex[philo->id]);
}

/// @brief
/// @param philo
void	philo_think(t_philos *philo)
{
	pthread_mutex_lock(&philo->vars->mutex[philo->id]);
	philo->state = THINKING;
	pthread_mutex_lock(&philo->vars->printf_mutex[philo->id]);
	printf("%lld ", get_time_in_ms() - philo->vars->start_time);
	printf("%ld is thinking\n", philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mutex[philo->id]);
	pthread_mutex_unlock(&philo->vars->mutex[philo->id]);
}

