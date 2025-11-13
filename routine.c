/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:43:06 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/13 16:13:18 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	monitoring_routine(void *arg)
{
	t_args	*vars;
	long	i;

	vars = (t_args *)arg;
	i = 0;
	while (i < vars->philos_num)
	{
		vars->delta[i] = get_time_in_ms() - vars->philos[i].last_meal;
		if (vars->delta[i] > vars->time_to_die)
		{
			pthread_mutex_lock(&vars->monitor_mutex);
			vars->philos[i].state = DEAD;
			vars->death_occured = 1;
			printf(R"LOL, philo %ld Died, F's in the Chat"RESET "\n",
				vars->philos[i].id);
			pthread_mutex_unlock(&vars->monitor_mutex);
		}
	}
}

void	routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->parity == ODD)
		usleep(philo->vars->time_to_eat / 2);
	while (!philo->vars->death_occured)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}

void	philo_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	printf(G"%lld %ld has taken a fork"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_lock(&philo->left_fork->fork);
	printf(G"%lld %ld has taken a fork"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	printf(B"%lld %ld is eating"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	usleep(philo->vars->time_to_eat);
	philo->meal_counter++;
	philo->full = 1;
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	philo_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->vars->printf_mutex[philo->id]);
	printf(Y"%lld %ld is sleeping"RESET"\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	usleep(philo->vars->time_to_sleep);
	philo->full = 0;
	pthread_mutex_unlock(&philo->vars->printf_mutex[philo->id]);
}

void	philo_think(t_philos *philo)
{
	pthread_mutex_lock(&philo->vars->printf_mutex[philo->id]);
	printf(G"%lld %ld is thinking"RESET"\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mutex[philo->id]);
	pthread_mutex_lock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

