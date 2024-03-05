/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:46:28 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/05 16:15:16 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_numerics(char *s)
{
	if (!(*s == '+' || *s == '-' || (*s >= '0' && *s <= '9')))
		return (1);
	if ((*s == '+' || *s == '-' ) && (!(*(s + 1) >= '0' && *(s + 1) <= '9')))
		return (1);
	if (*s == '+' || *s == '-')
		s++;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			s++;
		else
			return (1);
	}
	return (0);
}

long int	ft_atol(char *str)
{
	long int	nb;

	nb = 0;
	while (*str == ' ' || (9 <= *str && *str <= 13))
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
		{
			write(2, "Parameter can not be negative\n", 31);
			exit(1);
		}
		str++;
	}
	while (47 < *str && *str < 58)
	{
		nb = nb * 10 + (*str - 48);
		str++;
	}
	return (nb);
}

static int	check_args(char *argv)
{
	long int	check;

	if ((check_numerics(argv)) || (ft_strlen(argv) == 0))
	{
		write(2, "Enter numeric parameters\n", 26);
		exit(1);
	}
	check = ft_atol(argv);
	if ((check > INT_MAX) || (ft_strlen(argv) > 10))
	{
		write(2, "Parameter is not in INT limits\n", 32);
		exit(1);
	}
	return (check);
}

void	set_args(char **argv, t_args *args)
{
	args->number_of_philosophers = check_args(argv[1]);
	args->time_to_die = check_args(argv[2]) * 1000;
	args->time_to_eat = check_args(argv[3]) * 1000;
	args->time_to_sleep = check_args(argv[4]) * 1000;
	if (argv[5])
		args->must_eat = check_args(argv[5]);
	else
		args->must_eat = -1;
	if ((args->time_to_die < 60000) || (args->time_to_eat < 60000) \
	|| (args->time_to_sleep < 60000))
	{
		write(2, \
			"Use numbers more than 60 or less than 2147483\n", \
			47);
		exit(1);
	}
}
