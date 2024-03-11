/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:29:27 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/11 14:30:36 by rtavabil         ###   ########.fr       */
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
	long int		number_of_philosophers;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		must_eat;
	t_fork			*forks;
	t_philo			*philos;
	long int		start;
	long int		end;

	pthread_mutex_t	mutex;
	long int		all_ready;
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
	t_fork		*first;
	t_fork		*second;
	int			full;
	t_args		*args;
}		t_philo;

void		set_args(char **argv, t_args *args);
void		init(t_args *args);
long int	ft_atol(char *str);

int			ft_strncmp(char *s1, char *s2, int n);
int			ft_strlen(char *str);

void		ft_thread(pthread_t *thread, \
	void *(f)(void *), void *data, char *func);
void		ft_mutex(pthread_mutex_t *mutex, char *func);

void		*ft_malloc(int size);
#endif
