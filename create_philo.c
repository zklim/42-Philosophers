/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:26:28 by zhlim             #+#    #+#             */
/*   Updated: 2023/08/25 14:15:47 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_philo(t_philo *philo, t_states *states)
{
    philo->states = states;
}

t_philo    *init_philos(t_states *states)
{
    int i;

    i = 0;
    states->philos = malloc(sizeof(t_philo) * states->number_philos);
    if (!states->philos)
        return (NULL);
    while (i < states->number_philos)
    {
        init_philo(&states->philos[i], states);
        i++;
    }
    return (states->philos);
}

int    create_philo(t_states *states)
{
    if (!init_philos(states))
        return (1);
    return (0);
}