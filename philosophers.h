/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:29:27 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/21 18:29:51 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <errno.h> //error codes

typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_args
{
	long int	number_of_philosophers;
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	long int	number_of_times_each_philosopher_must_eat;
	t_fork	*forks;
	t_philo	*philos;
	long int	start;
	long int	end;
}		t_args;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	long			fork_id;
}		t_fork;

typedef struct s_philo
{
	int			index;
	pthread_t	thread;
	int			eat_count;
	long int	last_eat;
	t_fork		*left;
	t_fork		*right;
	int			full;
}		t_philo;

void		set_args(char **argv, t_args *args);
long int	ft_atol(char *str);

#endif