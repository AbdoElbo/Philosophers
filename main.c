/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:56:40 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/10 18:04:13 by aelbouaz         ###   ########.fr       */
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

	philo = (t_philos *)arg;
	pthread_mutex_lock(&philo->vars->printf_mutex);
	printf("philo : %ld\n", philo->vars->philos_num);
	pthread_mutex_unlock(&philo->vars->printf_mutex);
}

int	main(int argc, char **argv)
{
	t_args	vars;

	if (!error_handle(argc, argv))
		return (1);
	if (!initialise_vars_1(&vars, argc, argv) || !initialise_vars_2(&vars)
		|| !initialise_vars_3(&vars))
		return (1);
	start_mutexes(&vars);
	if (!initialise_threads(&vars, routine))
		return (cleanup(&vars, 1), 1);
	print_status(vars);
	return (cleanup(&vars, 1), 0);
}
