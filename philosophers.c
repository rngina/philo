/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:27:43 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/22 15:21:38 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc == 5 || argc == 6)
	{
		set_args(argv, &args);
		printf("num_of_philosophers = %ld\n", args.number_of_philosophers);
		printf("time_to_die = %ld us\n", args.time_to_die);
		printf("time_to_eat = %ld us\n", args.time_to_eat);
		printf("time_to_sleep = %ld us\n", args.time_to_sleep);
		printf("number_of_times_each_philosopher_must_eat = %ld\n",
			args.number_of_times_each_philosopher_must_eat);
	}
	else
		write(2, "Invalid number of arguments\n", 29);
}
