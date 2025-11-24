/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:08:04 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/24 12:57:55 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

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
