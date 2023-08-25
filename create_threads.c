/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:20:36 by zhlim             #+#    #+#             */
/*   Updated: 2023/08/25 14:12:02 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine(void *args)
{
    t_philo    *philo;

    philo = (t_philo *)args;
    printf("thread id: %d\n", philo->id);
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
    return (0);
}