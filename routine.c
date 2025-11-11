/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:43:06 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/11 16:03:44 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

/// @brief
/// @param philo
void	philo_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->left_fork->fork);
	sleep(philo->vars->time_to_eat);
	pthread_mutex_lock(&philo->vars->mutex[philo->id]);
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
	usleep(time);
	pthread_mutex_lock(&philo->vars->mutex[philo->id]);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->vars->mutex[philo->id]);
}

/// @brief
/// @param philo
void	philo_think(t_philos *philo)
{
	pthread_mutex_lock(&philo->vars->mutex[philo->id]);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->vars->mutex[philo->id]);
}

