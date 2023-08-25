/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:16:06 by zhlim             #+#    #+#             */
/*   Updated: 2023/08/25 17:39:20 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    free_philo(t_philo *philos)
{
    free(philos);
}

void    free_forks(t_states *states, int end)
{
    int i;

    i = 0;
    while (i < end)
    {
        pthread_mutex_destroy(&states->philos[i].fork_l);
        i++;
    }
}

void    ft_free(t_states *states)
{
    free_forks(states, states->number_philos);
    free_philo(states->philos);
}