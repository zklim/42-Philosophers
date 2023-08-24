/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:50:15 by zhlim             #+#    #+#             */
/*   Updated: 2023/08/24 17:55:08 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

typedef struct  s_states
{
    int             number_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             times_must_eat;
    int             someone_died;
    struct s_philo  *philos;
    pthread_mutex_t *forks;
}           t_states;

typedef struct  s_philo
{
    t_states        *states;
    pthread_t       thread;
    pthread_mutex_t fork_l;
    pthread_mutex_t *fork_r;
}           t_philo;

int    create_philo(t_states *states);

#endif