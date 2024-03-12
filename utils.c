/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:07:52 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/12 14:27:13 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long time, t_args *args)
{
	long	start;

	start = gettime("microsecond");
	while (gettime("microsecond") - start < time)
	{
		if (args->end)
			break;
		usleep(1000);
	}	
}