/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:07:52 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/21 18:43:59 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	gettime(char *str)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit (1);
	if (ft_strncmp(str, "sec", 4) == 0)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (ft_strncmp(str, "milli", 6) == 0)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (ft_strncmp(str, "micro", 6) == 0)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	return (1);
}

void	ft_usleep(long time, t_args *args)
{
	long	start;
	long	rem;

	start = gettime("micro");
	while (gettime("micro") - start < time)
	{
		if (get_bool(&args->args_mutex, &args->end))
			break ;
		rem = time - (gettime("micro") - start);
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while (gettime("micro") - start < time)
				;
	}
}

void	ft_print(t_philo *philo, char *str)
{
	ft_mutex(&philo->args->pr_mutex, "lock");
	if (!ft_strncmp("eat", str, 4) && !philo->args->end)
		printf("%ld %d  is eating\n", gettime("milli") \
				- philo->args->start, philo->index);
	if (!ft_strncmp("sleep", str, 6) && !philo->args->end)
		printf("%ld %d  is sleeping\n", gettime("milli") \
				- philo->args->start, philo->index);
	if (!ft_strncmp("think", str, 6) && !philo->args->end)
		printf("%ld %d  is thinking\n", gettime("milli") \
				- philo->args->start, philo->index);
	if (!ft_strncmp("fork", str, 5) && !philo->args->end)
		printf("%ld %d  has taken a fork\n", gettime("milli") \
				- philo->args->start, philo->index);
	if (!ft_strncmp("died", str, 5) && \
		get_bool(&philo->args->args_mutex, &philo->args->end))
		printf("%ld %d  died\n", gettime("milli") - \
				philo->args->start, philo->index);
	ft_mutex(&philo->args->pr_mutex, "unlock");
}
