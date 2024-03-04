/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:40:21 by rtavabil          #+#    #+#             */
/*   Updated: 2024/03/04 15:02:29 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_malloc(int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		write(2, "Malloc did not work correctly\n", 31);
		exit(1);
	}
	return (ptr);
}

void	mutex_error(int status)
{
	if (status == 0)
		return ;
	if (status != 0)
	{
		write (2, "Mutex error\n", 13);
		exit(1);
	}
}

void	ft_mutex(pthread_mutex_t *mutex, char *func)
{
	if (ft_strncmp(func, "lock", 4))
		mutex_error(pthread_mutex_lock(mutex));
	else if (ft_strncmp(func, "unlock", 6))
		mutex_error(pthread_mutex_unlock(mutex));
	else if (ft_strncmp(func, "init", 4))
		mutex_error(pthread_mutex_init(mutex, NULL));
	else if (ft_strncmp(func, "destroy", 7))
		mutex_error(pthread_mutex_destroy(mutex));
}

void	thread_error(int status)
{
	if (status == 0)
		return ;
	if (status != 0)
	{
		write(2, "Pthread error\n", 15);
		exit(1);
	}
}

void	ft_thread(pthread_t *thread, void *(f)(void *), void *data, char *func)
{
	if (ft_strncmp(func, "create", 6))
		pthread_create(thread, NULL, f, data);
	else if (ft_strncmp(func, "join", 4))
		pthread_join(*thread, NULL);
	else if (ft_strncmp(func, "detach", 6))
		pthread_detach(*thread);
}
