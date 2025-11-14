/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:43:06 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/14 15:17:08 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*monitoring_routine(void *arg)
{
	t_args	*vars;
	long	i;

	vars = (t_args *)arg;
	while (vars->threads_ready == 0)
		usleep(1);
	pthread_mutex_lock(&vars->start_sim);
	vars->start_time = get_time_in_ms();
	pthread_mutex_unlock(&vars->start_sim);
	i = 0;
	while (!vars->death_occured)
	{
		if (i == vars->philos_num)
			i = 0;
		vars->delta[i] = (get_time_in_ms() - vars->philos[i].last_meal);
		printf(M"%lld delta[%ld] is %lld"RESET "\n",
			get_time_in_ms() - vars->start_time, i, vars->delta[i]);
		if (vars->delta[i] >= vars->time_to_die / 1000)
		{
			pthread_mutex_lock(&vars->monitor_mutex);
			vars->death_occured = 1;
			printf(R"LOL, philo %ld Died, F's in the Chat"RESET "\n",
				vars->philos[i].id);
			pthread_mutex_unlock(&vars->monitor_mutex);
		}
		i++;
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(&philo->vars->start_sim);
	philo->vars->threads++;
	if (philo->vars->threads == philo->vars->philos_num)
		philo->vars->threads_ready = 1;
	pthread_mutex_unlock(&philo->vars->start_sim);
	while (philo->vars->threads_ready == 0)
		usleep(1);
	if (philo->parity == ODD)
		usleep(philo->vars->time_to_eat / 2);
	while (!philo->vars->death_occured)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
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

