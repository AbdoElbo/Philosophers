/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:08:04 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/12/11 20:06:57 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

/// @brief safely return the value of dst
long	get_long(pthread_mutex_t *mutex, long *dst)
{
	long	number;

	pthread_mutex_lock(mutex);
	number = *dst;
	pthread_mutex_unlock(mutex);
	return (number);
}

/// @brief safely set "dst" to "Updated"
void	set_long(pthread_mutex_t *mutex, long *dst, long updated)
{
	pthread_mutex_lock(mutex);
	*dst = updated;
	pthread_mutex_unlock(mutex);
}

/// @brief safely return the value of dst
long long	get_long_long(pthread_mutex_t *mutex, long long *dst)
{
	long long	number;

	pthread_mutex_lock(mutex);
	number = *dst;
	pthread_mutex_unlock(mutex);
	return (number);
}

/// @brief safely set "dst" to "Updated"
void	set_long_long(pthread_mutex_t *mutex, long long *dst, long long updated)
{
	pthread_mutex_lock(mutex);
	*dst = updated;
	pthread_mutex_unlock(mutex);
}

void	handle_one_philo(t_args *vars)
{
	if (vars->color == true)
	{
		printf(G"0 1 has taken a fork"RESET "\n");
		usleep(vars->time_to_die * 1000);
		printf(R "0 %ld died"RESET "\n", vars->time_to_die);
	}
	else
	{
		printf("0 1 has taken a fork\n");
		usleep(vars->time_to_die * 1000);
		printf("0 %ld died\n", vars->time_to_die);
	}
}
