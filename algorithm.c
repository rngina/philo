/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:25:05 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/21 18:57:18 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all(philo->args);
	ft_mutex(&philo->args->args_mutex, "lock");
	philo->args->num_th++;
	ft_mutex(&philo->args->args_mutex, "unlock");
	ft_mutex(&philo->mutex, "lock");
	philo->last_eat = gettime("milli");
	ft_mutex(&philo->mutex, "unlock");
	while (!is_finished(philo->args))
	{
		if (get_bool(&philo->mutex, &philo->full))
			break ;
		eat(philo);
		ft_print(philo, "sleep");
		ft_usleep(philo->args->t_sleep, philo->args);
		think(philo);
	}
	return (NULL);
}

int	is_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->mutex, &philo->full))
		return (0);
	elapsed = gettime("milli") - get_long(philo,
			&philo->last_eat);
	t_to_die = philo->args->t_die / 1e3;
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
		while (i < args->num_phil && !is_finished(args))
		{
			if (is_died(args->philos + i))
			{
				ft_mutex(&args->args_mutex, "lock");
				args->end = 1;
				ft_mutex(&args->args_mutex, "unlock");
				ft_print(args->philos + i, "died");
				break ;
			}
			i++;
		}
	}
	return (NULL);
}

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all(philo->args);
	ft_mutex(&philo->args->args_mutex, "lock");
	philo->args->num_th++;
	ft_mutex(&philo->args->args_mutex, "unlock");
	ft_mutex(&philo->mutex, "lock");
	philo->last_eat = gettime("milli");
	ft_mutex(&philo->mutex, "unlock");
	ft_print(philo, "fork");
	while (!is_finished(philo->args))
		usleep(100);
	return (NULL);
}

void	algorithm(t_args *args)
{
	int	i;

	i = -1;
	if (args->must_eat == 0)
		return ;
	if (args->num_phil == 1)
		ft_thread(&args->philos[0].thread, one_philo, \
				&args->philos[0], "create");
	else
		while (++i < args->num_phil)
			ft_thread(&args->philos[i].thread, dinner, \
					&args->philos[i], "create");
	ft_thread(&args->monitor, monitor, args, "create");
	args->start = gettime("milli");
	ft_mutex(&args->args_mutex, "lock");
	args->all_ready = 1;
	ft_mutex(&args->args_mutex, "unlock");
	i = -1;
	while (++i < args->num_phil)
		ft_thread(&args->philos[i].thread, dinner, &args->philos[i], "join");
	ft_mutex(&args->args_mutex, "lock");
	args->end = 1;
	ft_mutex(&args->args_mutex, "unlock");
	ft_thread(&args->monitor, monitor, args, "join");
}
