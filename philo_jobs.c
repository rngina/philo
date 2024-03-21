/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:47:14 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/21 18:57:44 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	ft_mutex(&philo->first->fork, "lock");
	ft_print(philo, "fork");
	ft_mutex(&philo->second->fork, "lock");
	ft_print(philo, "fork");
	philo->eat_count++;
	ft_mutex(&philo->mutex, "lock");
	philo->last_eat = gettime("milli");
	ft_mutex(&philo->mutex, "unlock");
	ft_print(philo, "eat");
	ft_usleep(philo->args->t_eat, philo->args);
	if ((philo->eat_count > 0) && (philo->eat_count == philo->args->must_eat))
	{
		ft_mutex(&philo->mutex, "lock");
		philo->full = 1;
		ft_mutex(&philo->mutex, "unlock");
	}
	ft_mutex(&philo->first->fork, "unlock");
	ft_mutex(&philo->second->fork, "unlock");
}

void	think(t_philo *philo)
{
	ft_print(philo, "think");
	if (philo->args->num_phil % 2 == 1)
	{
		ft_usleep(philo->args->t_eat / 2, philo->args);
	}
}
