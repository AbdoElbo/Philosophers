/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:08:04 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/11 16:02:32 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

/// @brief parsing the args and store them in vars
/// @param vars
/// @param argc
/// @param argv
/// @return always return 1 (because we're calling it in main in an if statement
///to make the code cleaner)
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
	vars->start_time = get_time_in_ms();
	vars->delta = 0;
	vars->death_occured = 0;
	return (1);
}

/// @brief allocates memory for all mutexes and threads
/// @param vars
/// @return returns 1 on success, 0 on failure
int	initialise_vars_2(t_args *vars)
{
	vars->monitoring = NULL;
	vars->philos = NULL;
	vars->forks = NULL;
	vars->printf_mutex = NULL;
	vars->monitoring = malloc(sizeof(pthread_t));
	if (!vars->monitoring)
		return (0);
	vars->philos = malloc(sizeof(t_philos) * (vars->philos_num + 1));
	if (!vars->philos)
		return (0);
	vars->forks = malloc(sizeof(t_forks) * vars->forks_num);
	if (!vars->forks)
		return (0);
	vars->printf_mutex = malloc(sizeof(pthread_mutex_t) * vars->forks_num);
	if (!vars->printf_mutex)
		return (0);
	vars->mutex = malloc(sizeof(pthread_mutex_t) * vars->forks_num);
	if (!vars->mutex)
		return (0);
	return (1);
}

/// @brief initialising vars for each philo (forks, states,...)
/// @param vars
/// @return always return 1 (because we're calling it in main in an if statement
///to make the code cleaner)
int	initialise_vars_3(t_args *vars)
{
	long	i;

	i = 0;
	while (i < vars->philos_num - 1)
	{
		if ((i + 1) % 2 == 0)
			vars->philos[i].state = IDLE;
		else
			vars->philos[i].state = EATING;
		vars->philos[i].right_fork = &vars->forks[i];
		vars->philos[i].left_fork = &vars->forks[i + 1];
		vars->philos[i].full = false;
		vars->philos[i].meal_counter = 0;
		vars->philos[i].id = i;
		vars->forks[i].fork_id = i;
		i++;
	}
	vars->philos[i].right_fork = &vars->forks[i];
	vars->philos[i].left_fork = &vars->forks[0];
	vars->philos[i].full = false;
	vars->philos[i].meal_counter = 0;
	vars->forks[i].fork_id = i;
	if (vars->philos_num % 2 == 1 && vars->philos_num != 1)
		vars->philos[vars->philos_num - 1].state = IDLE;
	return (1);
}

int	initialise_threads(t_args *vars, void (routine)(void *arg))
{
	long	i;

	i = 0;
	while (i < vars->philos_num)
	{
		vars->philos[i].vars = vars;
		if (pthread_create(&vars->philos[i].th, NULL
				, (void *)routine, &vars->philos[i]))
			return (cleanup(vars, 1), 0);
		i++;
	}
	i = 0;
	while (i < vars->philos_num)
	{
		if (pthread_join(vars->philos[i].th, NULL))
			return (cleanup(vars, 1), 0);
		i++;
	}
	return (1);
}

long long	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
