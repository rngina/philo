/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:25:05 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/13 17:23:13 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_bool(pthread_mutex_t *args_mutex, long int *value)
{
	int	ret;

	ft_mutex(args_mutex, "lock");
	ret = *value;
	ft_mutex(args_mutex, "unlock");
	return (ret);
}

void	wait_all(t_args *args)
{
	while (!get_bool(&args->args_mutex, &args->all_ready))
		;
}

void	eat(t_philo *philo)
{
	ft_mutex(&philo->first->fork, "lock");
	ft_print(philo, "fork");
	ft_mutex(&philo->second->fork, "lock");
	ft_print(philo, "fork");
	//should there be mutex for philo?
	philo->eat_count++;
	philo->last_eat = gettime("millisecond");
	ft_print(philo, "eat");
	ft_usleep(philo->args->time_to_eat, philo->args);
	if ((philo->eat_count > 0) && (philo->eat_count == philo->args->must_eat))
		philo->full = 1;
	ft_mutex(&philo->first->fork, "unlock");
	ft_mutex(&philo->second->fork, "unlock");
}

void	think(t_philo *philo)
{
	ft_print(philo, "think");
}

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all(philo->args);
//feels like should add mutex here
	while (!philo->args->end)
	{
		if (philo->full)
			break ;
//eat
	eat(philo);
//sleep
	ft_print(philo, "sleep");
	ft_usleep(philo->args->time_to_sleep, philo->args);
//think
	think(philo);
	}
	return (NULL);
}

long	gettime(char *str)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit (1);
	if (ft_strncmp(str, "second", 7) == 0)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (ft_strncmp(str, "millisecond", 12) == 0)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (ft_strncmp(str, "microsecond", 12) == 0)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	return (1);
}

void	monitor(void *data)
{
	t_args	*args;

	args = (t_args *)data;
	
	return (NULL);
}

void	algorithm(t_args *args)
{
	int	i;

	if (args->must_eat == 0)
		return ;
	i = 0;
	while (i < args->number_of_philosophers)
	{
		ft_thread(&args->philos[i].thread, dinner, &args->philos[i], "create");
		i++;
	}
	ft_thread(&args->monitor, monitor, args, "create");

	args->start = gettime("millisecond");
	ft_mutex(&args->args_mutex, "lock");
	args->all_ready = 1;
	ft_mutex(&args->args_mutex, "unlock");
	i = 0;
	while (i < args->number_of_philosophers)
	{
		ft_thread(&args->philos[i].thread, &dinner, &args->philos, "join");
		printf("thread %d joined\n", i);
		i++;
	}
}
