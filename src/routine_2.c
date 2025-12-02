/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:02:30 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/12/02 20:03:43 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	philo_eat(t_philos *philo)
{
	int	first;
	int	second;

	first = philo->right_fork->fork_id;
	second = philo->left_fork->fork_id;
	if (!(get_long(&philo->vars->set_read_mtx, &philo->vars->sim_end)))
	{
		if (first < second)
			lock_right_fork_first(philo);
		else
			lock_left_fork_first(philo);

		pthread_mutex_lock(&philo->vars->printf_mtx);
		printf("%lld %ld is eating" "\n",
			get_time_in_ms() - philo->vars->start_time, philo->id + 1);
		pthread_mutex_unlock(&philo->vars->printf_mtx);

		set_long_long(&philo->vars->time_mtx, &philo->last_meal,
			get_time_in_ms());

		usleep(philo->vars->time_to_eat * 1000);
		pthread_mutex_lock(&philo->vars->set_read_mtx);
		philo->meal_counter++;
		pthread_mutex_unlock(&philo->vars->set_read_mtx);

		if (get_long(&philo->vars->set_read_mtx, &philo->meal_counter)
			== philo->vars->meals_to_eat)
		{
			pthread_mutex_lock(&philo->vars->set_read_mtx);
			philo->vars->meals_tracker++;
			pthread_mutex_unlock(&philo->vars->set_read_mtx);
			// pthread_mutex_lock(&philo->vars->printf_mtx);
			// printf(M"%lld %ld has eaten LAST meal "RESET "\n",
			// 	get_time_in_ms() - philo->vars->start_time, philo->id);
			// pthread_mutex_unlock(&philo->vars->printf_mtx);
		}

		pthread_mutex_unlock(&philo->right_fork->fork);
		pthread_mutex_unlock(&philo->left_fork->fork);
	}
}

void	lock_right_fork_first(t_philos *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf("%lld %ld has taken a fork" "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf("%lld %ld has taken a fork" "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
}

void	lock_left_fork_first(t_philos *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf("%lld %ld has taken a fork" "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
	pthread_mutex_lock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf("%lld %ld has taken a fork" "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->vars->printf_mtx);
}

void	philo_sleep(t_philos *philo)
{
	if (!(get_long(&philo->vars->set_read_mtx, &philo->vars->sim_end)))
	{
		pthread_mutex_lock(&philo->vars->printf_mtx);
		printf("%lld %ld is sleeping""\n",
			get_time_in_ms() - philo->vars->start_time, philo->id + 1);
		pthread_mutex_unlock(&philo->vars->printf_mtx);
		usleep(philo->vars->time_to_sleep * 1000);
	}
}

void	philo_think(t_philos *philo)
{
	long	margin;
	long	think_time;

	if (!(get_long(&philo->vars->set_read_mtx, &philo->vars->sim_end)))
	{
		pthread_mutex_lock(&philo->vars->printf_mtx);
		printf("%lld %ld is thinking""\n",
			get_time_in_ms() - philo->vars->start_time, philo->id + 1);
		pthread_mutex_unlock(&philo->vars->printf_mtx);
		margin = (philo->vars->time_to_eat * 1000 * philo->vars->philos_num) / 100;
		think_time = philo->vars->time_to_eat - philo->vars->time_to_sleep;
		if (philo->vars->time_to_sleep <= philo->vars->time_to_eat)
			usleep((think_time * 1000) + margin);
		else
			usleep(margin);
	}
}

