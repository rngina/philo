//include "philosophers.h"

// long    gettime(char *str)
// {
//     struct timeval  tv;

//     if (gettimeofday(&tv, NULL))
//         exit ;
//     if (ft_strncmp(str, "second", 7) == 0)
//         return (tv.tv_sec + tv.tv_usec / 1e6);
//     else if (ft_strncmp(str, "millisecond", 13) == 0)
//         return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
//     else if (ft_strncmp(str, "microsecond", 13) == 0)
//         return (tv.tv_sec * 1e6 + tv.tv_usec);
//     return (1);
// }

#include <stdio.h>

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] < s2[i])
			return (-1);
		if (s2[i] < s1[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_print(char *str)
{
//	ft_mutex(&philo->args->print_mutex, "lock");
	if (!ft_strncmp("eat", str, 4))
		printf(" is eating\n");
	//ft_mutex(&philo->args->print_mutex, "unlock");
}

int main()
{
	ft_print("eat");
}

// void    *routine()
// {
//   //  usleep(1000000);
//     printf("Finished execution\n");
// }

// int main(int argc, char **argv)
// {
//     pthread_t *th;
//     int number_of_ph;

//     number_of_ph = (int)ft_atol(argv[1]);
//     th = (pthread_t *)malloc(number_of_ph * sizeof(pthread_t));

//     for (int i = 0; i < number_of_ph; i++)
//     {
//         if (pthread_create(th + i, NULL, &routine, NULL) != 0)
//         {
//             perror("Thread was not created\n");
//             return (1);
//         }
//        pthread_detach(*(th + i));
//     }
//     // for (int i = 0; i < number_of_ph; i++)
//     // {
//     //     if (pthread_join(th[i], NULL) != 0)
//     //         return (2);
//     // }
//     free(th);
//     pthread_exit(0);
// }

