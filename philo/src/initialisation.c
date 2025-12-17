/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:08:04 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/12/16 12:59:26 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	initialise_vars_1(t_args *vars, int argc, char **argv)
{
	vars->philos_num = ft_atol(argv[1]);
	vars->forks_num = vars->philos_num;
	vars->time_to_die = ft_atol(argv[2]);
	vars->time_to_eat = ft_atol(argv[3]);
	vars->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		vars->meals_to_eat = ft_atol(argv[5]);
	else
		vars->meals_to_eat = -2;
	vars->threads_ready = 0;
	vars->sim_end = 0;
	vars->philos = NULL;
	vars->forks = NULL;
	vars->meals_tracker = 0;
	vars->philos = malloc(sizeof(t_philos) * (vars->philos_num));
	if (!vars->philos)
		return (0);
	vars->forks = malloc(sizeof(t_forks) * vars->forks_num);
	if (!vars->forks || !vars->philos)
		return (0);
	if (vars->meals_to_eat == 0)
		return (0);
	return (1);
}

int	initialise_vars_2(t_args *vars)
{
	long	i;

	vars->cleanup_flag = 0;
	i = 0;
	while (i < vars->philos_num)
	{
		if (i % 2 == 0)
			vars->philos[i].parity = ODD;
		else
			vars->philos[i].parity = EVEN;
		vars->philos[i].right_fork = &vars->forks[i];
		if (i == vars->philos_num - 1)
			vars->philos[i].left_fork = &vars->forks[0];
		else
			vars->philos[i].left_fork = &vars->forks[i + 1];
		vars->philos[i].meal_counter = 0;
		vars->philos[i].id = i;
		vars->forks[i].fork_id = i;
		vars->forks[i].ok = 0;
		i++;
	}
	return (1);
}

int	create_philos(t_args *vars, void *(philo_routine)(void *arg))
{
	long	i;
	long	j;

	i = 0;
	while (i < vars->philos_num)
	{
		vars->philos[i].vars = vars;
		if (pthread_create(&vars->philos[i].th, NULL
				, philo_routine, &vars->philos[i]))
		{
			set_long(&vars->set_read_mtx, &vars->sim_end, 1);
			set_long(&vars->set_read_mtx, &vars->threads_ready, 1);
			j = 0;
			while (j < i)
			{
				if (pthread_join(vars->philos[j].th, NULL))
					return (write (2, "Failed to join threads.\n", 24), 0);
				j++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	create_monitoring(t_args *vars, void *(monitoring_routine)(void *arg))
{
	long	j;

	vars->start_time = get_time_in_ms();
	if (pthread_create(&vars->monitoring, NULL, monitoring_routine, vars))
	{
		set_long(&vars->set_read_mtx, &vars->sim_end, 1);
		set_long(&vars->set_read_mtx, &vars->threads_ready, 1);
		j = 0;
		while (j < vars->philos_num)
		{
			if (pthread_join(vars->philos[j].th, NULL))
				return (write (2, "Failed to join threads.\n", 24), 0);
			j++;
		}
		return (0);
	}
	set_long(&vars->set_read_mtx, &vars->threads_ready, 1);
	return (1);
}

int	join_threads(t_args *vars)
{
	long	i;

	i = 0;
	while (i < vars->philos_num)
	{
		if (pthread_join(vars->philos[i].th, NULL))
			return (write (2, "Failed to join threads.\n", 24), 0);
		i++;
	}
	if (pthread_join(vars->monitoring, NULL))
		return (write (2, "Failed to join Monitoring thread.\n", 34), 0);
	return (1);
}
