/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:40:52 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/21 18:57:33 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_all(t_args *args)
{
	while (!get_bool(&args->args_mutex, &args->all_ready))
		;
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

int	get_bool(pthread_mutex_t *mutex, long int *value)
{
	int	ret;

	ft_mutex(mutex, "lock");
	ret = *value;
	ft_mutex(mutex, "unlock");
	return (ret);
}

int	all_threads_run(t_args *args)
{
	int	ret;

	ret = 1;
	ft_mutex(&args->args_mutex, "lock");
	if (args->num_phil == args->num_th)
		ret = 0;
	ft_mutex(&args->args_mutex, "unlock");
	return (ret);
}
