/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:43:06 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/24 12:55:57 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*monitoring_routine(void *arg)
{
	t_args		*vars;
	long long	delta;
	long		i;

	vars = (t_args *)arg;
	while (!(get_long(&vars->set_read_mtx, &vars->threads_ready)))
		usleep(1);
	i = 0;
	while (!(get_long(&vars->set_read_mtx, &vars->death_occured))
		&& !(get_long(&vars->set_read_mtx, &vars->sim_end)))
	{
		if (i == vars->philos_num)
			i = 0;
		delta = (get_time_in_ms()
				- get_long_long(&vars->time_mtx, &vars->philos[i].last_meal));
		if (delta >= vars->time_to_die)
		{
			set_long(&vars->philo_mtx, &vars->death_occured, 1);
			pthread_mutex_lock(&vars->printf_mtx);
			printf(R "%lld %ld died"RESET "\n",
				get_time_in_ms() - vars->start_time, vars->philos[i].id);
			pthread_mutex_unlock(&vars->printf_mtx);
		}
		i++;
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philos	*ph;

	ph = (t_philos *)arg;
	while (!(get_long(&ph->vars->set_read_mtx, &ph->vars->threads_ready)))
		usleep(1);
	ph->last_meal = ph->vars->start_time;
	if (ph->parity == ODD)
		usleep((ph->vars->time_to_eat * 1000) / 2);
	while (!(get_long(&ph->vars->set_read_mtx, &ph->vars->death_occured)))
	{
		if (get_long(&ph->vars->set_read_mtx, &ph->vars->meals_to_eat) != ph->meal_counter)
		{
			if (!(get_long(&ph->vars->set_read_mtx, &ph->vars->death_occured)))
				philo_eat(ph);
			if (!(get_long(&ph->vars->set_read_mtx, &ph->vars->death_occured)))
				philo_sleep(ph);
			if (!(get_long(&ph->vars->philo_mtx, &ph->vars->death_occured)))
				philo_think(ph);
		}
		else
			return (set_long(&ph->vars->philo_mtx, &ph->vars->sim_end, 1), NULL);
	}
	return (NULL);
}

void	philo_eat(t_philos *philo)
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

	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(B"%lld %ld is eating"RESET "\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mtx);

	usleep(philo->vars->time_to_eat * 1000);
	pthread_mutex_lock(&philo->vars->philo_mtx);
	philo->meal_counter++;
	philo->full = 1;
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
 // this is for testing meals
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	philo_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(Y"%lld %ld is sleeping"RESET"\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mtx);

	set_long(&philo->vars->philo_mtx, &philo->full, 0);
	usleep(philo->vars->time_to_sleep * 1000);
}

void	philo_think(t_philos *philo)
{
	pthread_mutex_lock(&philo->vars->printf_mtx);
	printf(G"%lld %ld is thinking"RESET"\n",
		get_time_in_ms() - philo->vars->start_time, philo->id);
	pthread_mutex_unlock(&philo->vars->printf_mtx);

	pthread_mutex_lock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

