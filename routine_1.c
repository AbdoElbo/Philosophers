/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:43:06 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/24 19:05:55 by aelbouaz         ###   ########.fr       */
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
	usleep(100);
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
			set_long(&vars->set_read_mtx, &vars->death_occured, 1);
			pthread_mutex_lock(&vars->printf_mtx);
			printf(R "%lld %ld died (delta is %lld)"RESET "\n",
				get_time_in_ms() - vars->start_time, vars->philos[i].id, delta);
			printf(R "epoch is %lld"RESET "\n", get_time_in_ms());
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
	set_long_long(&ph->vars->time_mtx, &ph->last_meal, ph->vars->start_time);
	if (ph->parity == ODD)
		usleep(ph->vars->time_to_eat * 500);
	while (!(get_long(&ph->vars->set_read_mtx, &ph->vars->death_occured)))
	{
		if (get_long(&ph->vars->set_read_mtx, &ph->vars->meals_to_eat) != ph->meal_counter)
		{
			if (!(get_long(&ph->vars->set_read_mtx, &ph->vars->death_occured)))
				philo_eat(ph);
			if (!(get_long(&ph->vars->set_read_mtx, &ph->vars->death_occured)))
				philo_sleep(ph);
			if (!(get_long(&ph->vars->set_read_mtx, &ph->vars->death_occured)))
				philo_think(ph);
		}
		else
			return (set_long(&ph->vars->set_read_mtx, &ph->vars->sim_end, 1), NULL);
	}
	return (NULL);
}
