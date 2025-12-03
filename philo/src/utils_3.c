/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:22:04 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/12/03 15:06:40 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	lock_forks(t_philos *philo)
{
	int	first;
	int	second;

	first = philo->right_fork->fork_id;
	second = philo->left_fork->fork_id;
	if (first < second)
		lock_right_fork_first(philo);
	else
		lock_left_fork_first(philo);
}

void	lock_right_fork_first(t_philos *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(G"%lld %ld has taken a fork"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(G"%lld %ld has taken a fork"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
}

void	lock_left_fork_first(t_philos *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(G"%lld %ld has taken a fork"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
	pthread_mutex_lock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(G"%lld %ld has taken a fork"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
}
