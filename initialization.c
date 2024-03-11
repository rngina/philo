/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:51:27 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/11 14:39:23 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_args *args)
{
	int	i;
	int	num;

	i = 0;
	num = args->number_of_philosophers;
	while (i < num)
	{
		args->philos[i].index = i + 1;
		args->philos[i].full = 0;
		args->philos[i].eat_count = 0;
		args->philos[i].args = args;
		args->philos[i].first = &(args->forks[(i + 1) % num]);
		args->philos[i].second = &(args->forks[i]);
		if (i % 2 == 0)
		{
			args->philos[i].first = &(args->forks[i]);
			args->philos[i].second = &(args->forks[(i + 1) % num]);
		}
		i++;
	}
}

void	init(t_args *args)
{
	int	i;

	i = 0;
	args->end = 0;
	args->philos = (t_philo *)ft_malloc(sizeof(t_philo)
			* args->number_of_philosophers);
	args->forks = (t_fork *)ft_malloc(sizeof(t_fork)
			* args->number_of_philosophers);
	while (i < args->number_of_philosophers)
	{
		ft_mutex(&args->forks[i].fork, "init");
		args->forks[i].fork_id = i;
		i++;
	}
	args->all_ready = 0;
	init_philo(args);
}
