/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:51:27 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/04 18:22:03 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_args *args)
{
	int	i;

	i = 0;
	while(++i <= args->number_of_philosophers)
	{
		args->philos[i].index = i;
		args->philos[i].full = 0;
		args->philos[i].eat_count = 0;
		args->philos[i].args = args;
	}
}

void	init(t_args *args)
{
	int	i;

	i = 0;
	args->end = 0;
	args->philos = (t_philo *)ft_malloc(sizeof(t_philo) * args->number_of_philosophers);
	args->forks = (t_fork *)ft_malloc(sizeof(t_fork) * args->number_of_philosophers);
	while (++i <= args->number_of_philosophers)
	{
		ft_mutex(&args->forks[i].fork, "init");
		args->forks[i].fork_id = i;
	}
	
}