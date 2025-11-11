/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:56:40 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/11 15:57:11 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	print_status(t_args vars)
{
	long	i;

	i = 0;
	printf("\n");
	while (i < vars.philos_num)
	{
		if (vars.philos[i].state == THINKING)
			printf("status of philo %lu is : THINKING\n", i + 1);
		if (vars.philos[i].state == IDLE)
			printf("status of philo %lu is : IDLE\n", i + 1);
		if (vars.philos[i].state == EATING)
			printf("status of philo %lu is : EATING\n", i + 1);
		if (vars.philos[i].state == DEAD)
			printf("status of philo %lu is : DEAD\n", i + 1);
		i++;
	}
	i = 0;
	printf("\n");
	while (i < vars.philos_num)
	{
		printf("left fork for philo %ld, is %p\n", i, vars.philos[i].left_fork);
		printf("right fork for philo %ld, is %p\n", i, vars.philos[i].right_fork);
		i++;
	}
}
void	routine(void *arg)
{
	t_philos	*philo;
	int			i;

	i = 0;
	philo = (t_philos *)arg;
	if (i == 0 && !philo->vars->death_occured)
	{
		if (philo->state == EATING)
			philo_eat(philo);
		else
			philo_sleep(philo, 10);
		i++;
	}
	while (!philo->vars->death_occured)
	{
		philo_eat(philo);
		philo_sleep(philo, philo->vars->time_to_sleep);
		philo_think(philo);
	}
}

int	main(int argc, char **argv)
{
	t_args	vars;

	if (!error_handle(argc, argv))
		return (1);
	if (!initialise_vars_1(&vars, argc, argv) || !initialise_vars_2(&vars)
		|| !initialise_vars_3(&vars))
		return (cleanup(&vars, 0), 1);
	start_mutexes(&vars);
	if (!initialise_threads(&vars, routine))
		return (cleanup(&vars, 1), 1);
	// print_status(vars);
	return (cleanup(&vars, 1), 0);
}
