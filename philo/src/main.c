/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:56:40 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/12/11 20:00:30 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	main(int argc, char **argv)
{
	t_args	vars;

	if (!error_handle(argc, argv))
		return (1);
	if (!initialise_vars_1(&vars, argc, argv) || !initialise_vars_2(&vars))
		return (cleanup(&vars), 1);
	if (!start_mutexes(&vars))
		return (cleanup(&vars), 1);
	vars.color = false;
	if (vars.philos_num == 1)
	{
		handle_one_philo(&vars);
		return (cleanup(&vars), 0);
	}
	if (!create_philos(&vars, philo_routine))
		return (cleanup(&vars), 1);
	if (!create_monitoring(&vars, monitoring_routine))
		return (cleanup(&vars), 1);
	if (!join_threads(&vars))
		return (cleanup(&vars), 1);
	return (cleanup(&vars), 0);
}
