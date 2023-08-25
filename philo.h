/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:50:15 by zhlim             #+#    #+#             */
/*   Updated: 2023/08/25 17:39:52 by zhlim            ###   ########.fr       */
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

typedef struct  s_philo
{
    int             id;
    pthread_t       thread;
    pthread_mutex_t fork_l;
    pthread_mutex_t *fork_r;
    struct s_states *states;
}           t_philo;

typedef struct  s_states
{
    int             number_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             times_must_eat;
    int             someone_died;
    t_philo         *philos;
    pthread_mutex_t *forks;
}           t_states;

int     create_philo(t_states *states);
void    free_philo(t_philo *philos);
int    create_threads(t_states *states);
int    create_forks(t_states *states);
void    ft_free(t_states *states);
void    free_forks(t_states *states, int end);

#endif