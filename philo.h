/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:50:15 by zhlim             #+#    #+#             */
/*   Updated: 2023/08/31 17:35:53 by zhlim            ###   ########.fr       */
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

#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"

typedef struct  s_philo
{
    int             id;
    pthread_t       thread;
    pthread_mutex_t fork_l;
    pthread_mutex_t *fork_r;
    int             now;
    int             last_eat;
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
    unsigned long   start;
    t_philo         *philos;
    pthread_mutex_t lock;
}           t_states;

int     create_philo(t_states *states);
void    free_philo(t_philo *philos);
int    create_threads(t_states *states);
int    create_forks(t_states *states);
void    ft_free(t_states *states);
void    free_forks(t_states *states, int end);

#endif