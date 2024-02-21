#include "philosophers.h"

void    test(char *func)
{
    if (func == "lock")
        printf("It worked\n");    
}

int main()
{
    test("lock");
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

