/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:08:04 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/25 14:21:45 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	initialise_vars_1(t_args *vars, int argc, char **argv)
{
	vars->philos_num = ft_atol(argv[1]);
	vars->forks_num = vars->philos_num;
	vars->time_to_die = ft_atol(argv[2]);
	vars->time_to_eat = ft_atol(argv[3]);
	vars->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		vars->meals_to_eat = ft_atol(argv[5]);
		if (vars->meals_to_eat == 0)
			return (0);
	}
	else
		vars->meals_to_eat = -1;
	vars->death_occured = 0;
	vars->threads_ready = 0;
	vars->sim_end = 0;
	vars->philos = NULL;
	vars->forks = NULL;
	vars->philos = malloc(sizeof(t_philos) * (vars->philos_num));
	if (!vars->philos)
		return (0);
	vars->forks = malloc(sizeof(t_forks) * vars->forks_num);
	if (!vars->forks)
		return (0);
	return (1);
}

int	initialise_vars_2(t_args *vars)
{
	long	i;

	i = 0;
	while (i < vars->philos_num)
	{
		if ((i + 1) % 2 == 0)
			vars->philos[i].parity = EVEN;
		else
			vars->philos[i].parity = ODD;
		vars->philos[i].right_fork = &vars->forks[i];
		if (i == vars->philos_num - 1)
			vars->philos[i].left_fork = &vars->forks[0];
		else
			vars->philos[i].left_fork = &vars->forks[i + 1];
		vars->philos[i].full = 0;
		vars->philos[i].meal_counter = 0;
		vars->philos[i].id = i;
		vars->forks[i].fork_id = i;
		i++;
	}
	return (1);
}

int	initialise_threads(t_args *vars, void *(philo_routine)(void *arg)
		, void *(monitoring_routine)(void *arg))
{
	long	i;

	i = 0;
	while (i < vars->philos_num)
	{
		vars->philos[i].vars = vars;
		if (pthread_create(&vars->philos[i].th, NULL
				, philo_routine, &vars->philos[i]))
			return (cleanup(vars), 0);
		i++;
	}
	if (pthread_create(&vars->monitoring, NULL, monitoring_routine, vars))
		return (cleanup(vars), 0);
	vars->start_time = get_time_in_ms();
	set_long(&vars->set_read_mtx, &vars->threads_ready, 1);
	i = 0;
	while (i < vars->philos_num)
	{
		if (pthread_join(vars->philos[i].th, NULL))
			return (cleanup(vars), 0);
		i++;
	}
	if (pthread_join(vars->monitoring, NULL))
		return (cleanup(vars), 0);
	return (1);
}
