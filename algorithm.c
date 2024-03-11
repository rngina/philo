/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:25:05 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/11 16:37:35 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_bool(pthread_mutex_t *mutex, long int *value)
{
	int	ret;

	ft_mutex(mutex, "lock");
	ret = *value;
	ft_mutex(mutex, "unlock");
	return (ret);
}

void	wait_all(t_args *args)
{
	while (!get_bool(&args->mutex, &args->all_ready))
		;
}

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all(philo->args);
	return (NULL);
}

long	gettime(char *str)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit (1);
	if (ft_strncmp(str, "second", 7) == 0)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (ft_strncmp(str, "millisecond", 13) == 0)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (ft_strncmp(str, "microsecond", 13) == 0)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	return (1);
}

void	algorithm(t_args *args)
{
	int	i;

	if (args->must_eat == 0)
		return ;
	i = 0;
	while (i < args->number_of_philosophers)
	{
		ft_thread(&args->philos[i].thread, &dinner, &args->philos, "create");
		i++;
	}
	args->start = gettime("millisecond");
	ft_mutex(&args->mutex, "lock");
	args->all_ready = 1;
	ft_mutex(&args->mutex, "unlock");
	i = 0;
	while (i < args->number_of_philosophers)
	{
		ft_thread(&args->philos[i].thread, &dinner, &args->philos, "join");
		i++;
	}
}
