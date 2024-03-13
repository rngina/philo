/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:07:52 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/13 16:18:00 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long time, t_args *args)
{
	long	start;
	long	rem;

	start = gettime("microsecond");
	while (gettime("microsecond") - start < time)
	{
		if (args->end)
			break ;
		rem = time - (gettime("microsecond") - start);
		if (rem > 1e3)
		{
			usleep(rem / 2);
		}
		else
		{
			while (gettime("microsecond") - start < time)
				;
		}
	}
}

void	ft_print(t_philo *philo, char *str)
{
	ft_mutex(&philo->args->print_mutex, "lock");
	if (!ft_strncmp("eat", str, 4) && !philo->args->end)
		printf("%ld %d  is eating\n", gettime("millisecond") - philo->args->start, philo->index);
	if (!ft_strncmp("sleep", str, 6) && !philo->args->end)
		printf("%ld %d  is sleeping\n", gettime("millisecond") - philo->args->start, philo->index);
	if (!ft_strncmp("think", str, 6) && !philo->args->end)
		printf("%ld %d  is thinking\n", gettime("millisecond") - philo->args->start, philo->index);
	if (!ft_strncmp("fork", str, 5) && !philo->args->end)
		printf("%ld %d  has taken a fork\n", gettime("millisecond") - philo->args->start, philo->index);
	if (!ft_strncmp("died", str, 5) && !philo->args->end)
		printf("%ld %d  died\n", gettime("millisecond") - philo->args->start, philo->index);
	ft_mutex(&philo->args->print_mutex, "unlock");
}
