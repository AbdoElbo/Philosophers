/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:02:30 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/12/08 15:11:20 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	philo_eat(t_philos *philo)
{
	if (!(get_long(&philo->vars->set_read_mtx, &philo->vars->sim_end)))
	{
		lock_forks(philo);
		print_status(philo, "is eating", B);
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
		}
		pthread_mutex_unlock(&philo->right_fork->fork);
		pthread_mutex_unlock(&philo->left_fork->fork);
	}
}

void	philo_sleep(t_philos *philo)
{
	if (!(get_long(&philo->vars->set_read_mtx, &philo->vars->sim_end)))
	{
		print_status(philo, "is sleeping", W);
		usleep(philo->vars->time_to_sleep * 1000);
	}
}

void	philo_think(t_philos *philo)
{
	// long	margin;
	long	think_time;

	if (!(get_long(&philo->vars->set_read_mtx, &philo->vars->sim_end)))
	{
		print_status(philo, "is thinking", Y);
		think_time = philo->vars->time_to_eat - philo->vars->time_to_sleep;
		if (philo->vars->time_to_sleep <= philo->vars->time_to_eat)
			usleep((think_time * 1000) + 4000);
		else
			usleep(0);
	}
}
