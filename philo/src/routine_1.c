/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:43:06 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/12/05 19:10:26 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	death_checker(t_args *vars, long i)
{
	long long	delta;

	delta = (get_time_in_ms()
			- get_long_long(&vars->time_mtx, &vars->philos[i].last_meal));
	if (delta >= vars->time_to_die)
	{
		print_status(&vars->philos[i], "died", R);
		set_long(&vars->set_read_mtx, &vars->sim_end, 1);
	}
}

void	*monitoring_routine(void *arg)
{
	t_args		*vars;
	long		i;

	vars = (t_args *)arg;
	usleep((vars->time_to_eat * 1500) + (vars->philos_num * 100));	i = 0;
	while (!(get_long(&vars->set_read_mtx, &vars->sim_end)))
	{
		if (i == vars->philos_num)
			i = 0;
		if (get_long(&vars->set_read_mtx, &vars->meals_tracker)
			== vars->philos_num)
			set_long(&vars->set_read_mtx, &vars->sim_end, 1);
		death_checker(vars, i);
		usleep(50);
		i++;
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philos	*ph;

	ph = (t_philos *)arg;
	while (!(get_long(&ph->vars->set_read_mtx, &ph->vars->threads_ready)))
		usleep(150);
	set_long_long(&ph->vars->time_mtx, &ph->last_meal, ph->vars->start_time);
	if (ph->parity == ODD)
		usleep(ph->vars->time_to_eat * 500);
	if (ph->parity == EVEN && ph->id == ph->vars->philos_num - 1)
		usleep(ph->vars->time_to_eat * 1500);
	while (!(get_long(&ph->vars->set_read_mtx, &ph->vars->sim_end)))
	{
		if (get_long(&ph->vars->set_read_mtx, &ph->meal_counter)
			!= ph->vars->meals_to_eat + 1)
		{
			philo_eat(ph);
			philo_sleep(ph);
			philo_think(ph);
		}
	}
	return (NULL);
}
