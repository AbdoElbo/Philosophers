/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:03:13 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/11/10 14:28:53 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result >= 3000000000)
			return (result * sign);
		i++;
	}
	return (result * sign);
}

int	bigger_than_int(int argc, char **argv)
{
	int		i;
	long	num;

	i = 1;
	while (i < argc)
	{
		num = ft_atol(argv[i]);
		if (num > INT_MAX)
			return (1);
		else if (num < INT_MIN)
			return (1);
		i++;
	}
	return (0);
}

int	is_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int	error_handle(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (write(2, "Error:\nnumber of args invalid.\n", 31), 0);
	if (!is_digit(argc, argv))
		return (write(2, "Error:\nNon-Digit or Negative.\n", 30), 0);
	if (bigger_than_int(argc, argv))
		return (write(2, "Error:\nInt_Overflow.\n", 31), 0);
	return (1);
}
