/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:54:05 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/21 17:17:37 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free(t_args *args)
{
	int			i;
	t_philo	*cur;
	t_fork	*cur_f;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		cur = args->philos + i;
		ft_mutex(&cur->mutex, "destroy");
		i++;
	}
	i = 0;
	while (i < args->number_of_philosophers)
	{
		cur_f = args->forks + i;
		ft_mutex(&cur_f->fork, "destroy");
		i++;
	}
	ft_mutex(&args->args_mutex, "destroy");
	ft_mutex(&args->print_mutex, "destroy");
	free(args->forks);
	free(args->philos);
}