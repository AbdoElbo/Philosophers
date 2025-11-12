/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:56:40 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/12 14:18:37 by aelbouaz         ###   ########.fr       */
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
		if (vars.philos[i].parity == ODD)
			printf("Philo %lu is : ODD\n", i + 1);
		if (vars.philos[i].parity == EVEN)
			printf("Philo %lu is : EVEN\n", i + 1);
		i++;
	}
	printf("\n");
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
	print_status(vars);
	if (!initialise_threads(&vars, routine))
		return (cleanup(&vars, 1), 1);
	return (cleanup(&vars, 1), 0);
}
