/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekko <gekko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:56:40 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/08/02 22:49:33 by gekko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	main(int argc, char **argv)
{
	t_args	vars;

	if (!error_handle(argc, argv))
		return (1);
	if (!initialise_vars_1(&vars, argc, argv))
		return (cleanup(&vars), 1);
	if (!initialise_vars_2(&vars))
		return (cleanup(&vars), 1);
	if (!start_mutexes(&vars))
		return (cleanup(&vars), 1);
	vars.color = true;
	if (!create_philos(&vars, philo_routine))
		return (cleanup(&vars), 1);
	if (!create_monitoring(&vars, monitoring_routine))
		return (cleanup(&vars), 1);
	if (!join_threads(&vars))
		return (cleanup(&vars), 1);
	return (cleanup(&vars), 0);
}
