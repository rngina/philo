/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:40:21 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/21 18:39:55 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *ft_malloc(int size)
{
    void    *ptr;

    ptr = malloc(size);
    if (ptr == NULL)
    {
        write(2, "Malloc did not work correctly\n", 31);
        exit(1);
    }
    return (ptr);
}

void    mutex_error(int status, char *func)
{
    if (status == 0)
        return ;
    if ((status == EINVAL) && ((func == "lock") || (func == "unlock") || (func == "destroy")))
    {
        
    }
}

void    ft_mutex(pthread_mutex_t *mutex, char *func)
{
    if (func == "lock")
        pthread_mutex_lock(mutex);
    else if (func == "unlock")
        pthread_mutex_unlock(mutex);
    else if (func == "init")
        pthread_mutex_init(mutex, NULL);
    if (func == "destroy")
        pthread_mutex_destroy(mutex);  
}