/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:29:27 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/16 16:33:33 by rtavabil         ###   ########.fr       */
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

// typedef struct s_fork	t_fork;
// typedef struct s_philo	t_philo;
typedef struct s_args
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
	t_fork	*forks;
	t_philo	*philos;
	int		start;
	int		end;
}		t_args;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}		t_fork;

typedef struct s_philo
{
	int			index;
	pthread_t	thread;
	int			eat_count;
	long		last_eat;
	t_fork		*left;
	t_fork		*right;
	int			full;
}		t_philo;

void	set_args(char **argv, t_args *args);
long int	ft_atol(char *str);

#endif