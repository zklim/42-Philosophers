/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:20:36 by zhlim             #+#    #+#             */
/*   Updated: 2023/08/25 18:01:37 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine(void *args)
{
    t_philo    *philo;

    philo = (t_philo *)args;
    pthread_mutex_lock(&philo->fork_l);
    pthread_mutex_lock(philo->fork_r);
    printf("eating id: %d\n", philo->id);
    usleep(200);
    pthread_mutex_unlock(philo->fork_r);
    pthread_mutex_unlock(&philo->fork_l);
    if (philo->id == 6)
    {
        usleep(2000000);
        philo->states->someone_died = 1;
    }
    return (NULL);
}

int    create_threads(t_states *states)
{
    int i;
    int err;

    i = 0;
    while (i < states->number_philos)
    {
        states->philos[i].id = i + 1;
        err = pthread_create(&states->philos[i].thread, NULL, routine, &states->philos[i]);
        if (err)
            return (err);
        err = pthread_detach(states->philos[i].thread);
        if (err)
            return (err);
        i++;
    }
    // i = 0;
    // while (i < states->number_philos)
    // {
    //     if (i % 2 != 0)
    //     {
    //         states->philos[i].id = i + 1;
    //         err = pthread_create(&states->philos[i].thread, NULL, routine, &states->philos[i]);
    //         if (err)
    //             return (err);
    //         err = pthread_detach(states->philos[i].thread);
    //         if (err)
    //             return (err);
    //     }
    //     i++;
    // }
    return (0);
}