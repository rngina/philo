/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:29:27 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/21 18:56:25 by rtavabil         ###   ########.fr       */
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
	long int		num_phil;
	long int		t_die;
	long int		t_eat;
	long int		t_sleep;
	long int		must_eat;
	t_fork			*forks;
	t_philo			*philos;
	long int		start;
	long int		end;
	pthread_mutex_t	args_mutex;
	pthread_mutex_t	pr_mutex;
	long int		all_ready;
	pthread_t		monitor;
	long int		num_th;
}		t_args;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	long			fork_id;
}		t_fork;

typedef struct s_philo
{
	int				index;
	pthread_t		thread;
	int				eat_count;
	long int		last_eat;
	t_fork			*first;
	t_fork			*second;
	long			full;
	t_args			*args;
	pthread_mutex_t	mutex;
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
long		gettime(char *str);
void		ft_usleep(long time, t_args *args);
void		ft_print(t_philo *philo, char *str);
void		algorithm(t_args *args);
int			is_finished(t_args *args);
int			get_bool(pthread_mutex_t *mutex, long int *value);
void		ft_free(t_args *args);
void		wait_all(t_args *args);
long		get_long(t_philo *philo, long *value);
void		think(t_philo *philo);
void		eat(t_philo *philo);
int			all_threads_run(t_args *args);

#endif
