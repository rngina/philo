/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:25:05 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/20 18:37:22 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	ft_mutex(&philo->first->fork, "lock");
	ft_print(philo, "fork");
	ft_mutex(&philo->second->fork, "lock");
	ft_print(philo, "fork");
	//should there be mutex for philo?
	philo->eat_count++;

	ft_mutex(&philo->mutex, "lock");
	philo->last_eat = gettime("millisecond");
	ft_mutex(&philo->mutex, "unlock");


	ft_print(philo, "eat");
	ft_usleep(philo->args->time_to_eat, philo->args);
	if ((philo->eat_count > 0) && (philo->eat_count == philo->args->must_eat))
		philo->full = 1;
	ft_mutex(&philo->first->fork, "unlock");
	ft_mutex(&philo->second->fork, "unlock");
}

int	get_bool(pthread_mutex_t *args_mutex, long int *value)
{
	int	ret;

	ft_mutex(args_mutex, "lock");
	ret = *value;
	ft_mutex(args_mutex, "unlock");
	return (ret);
}
//put all in one function
void	think(t_philo *philo)
{
	ft_print(philo, "think");
}

void	wait_all(t_args *args)
{
	while (!get_bool(&args->args_mutex, &args->all_ready))
		;
}

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all(philo->args);
	ft_mutex(&philo->args->args_mutex, "lock");
	philo->args->num_threads++;
	ft_mutex(&philo->args->args_mutex, "unlock");
	ft_mutex(&philo->mutex, "lock");
	philo->last_eat = gettime("millisecond");
	ft_mutex(&philo->mutex, "unlock");
	while (!is_finished(philo->args))
	{
		if (get_bool(&philo->mutex, &philo->full))
			break ;
		eat(philo);
		ft_print(philo, "sleep");
		ft_usleep(philo->args->time_to_sleep, philo->args);
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

int	all_threads_run(t_args *args)
{
	int	ret;

	ret = 1;
	ft_mutex(&args->args_mutex, "lock");
	if (args->number_of_philosophers == args->num_threads)
		ret = 0;
	ft_mutex(&args->args_mutex, "unlock");
	return (ret);
}

long	get_long(t_philo *philo, long *value)
{
	long	ret;

	ft_mutex(&philo->mutex, "lock");
	ret = *value;
	ft_mutex(&philo->mutex, "unlock");
	return (ret);
}

int	is_finished(t_args *args)
{
	return (get_bool(&args->args_mutex, &args->end));
}

int	is_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->mutex, &philo->full))
		return (0);
	elapsed = gettime("millisecond") - get_long(philo,
			&philo->last_eat);
	t_to_die = philo->args->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (1);
	return (0);
}

void	*monitor(void *data)
{
	t_args	*args;
	int		i;

	args = (t_args *)data;
	while (all_threads_run(args))
		;
	while (!is_finished(args))
	{
		i = 0;
		while (i < args->number_of_philosophers && !is_finished(args))
		{
			if (is_died(args->philos + i))
			{
				ft_mutex(&args->args_mutex, "lock");
				args->end = 1;
				ft_mutex(&args->args_mutex, "unlock");
				ft_print(args->philos + i, "died");
				break;
			}
			i++;
		}
	}
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
		ft_thread(&args->philos[i].thread, NULL, NULL, "join");
		i++;
	}
	ft_thread(&args->monitor, NULL, NULL, "join");
}
