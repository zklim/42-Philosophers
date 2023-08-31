/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:20:36 by zhlim             #+#    #+#             */
/*   Updated: 2023/08/31 17:58:18 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long   get_timestamp(void)
{
    struct timeval  now;

    gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void    eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->states->lock);
    pthread_mutex_lock(&philo->fork_l);
    philo->now = get_timestamp() - philo->states->start;
    printf(RED "%d %d has taken a fork\n" RESET, philo->now, philo->id);
    pthread_mutex_lock(philo->fork_r);
    philo->now = get_timestamp() - philo->states->start;
    printf(MAGENTA "%d %d has taken a fork\n" RESET, philo->now, philo->id);
    pthread_mutex_unlock(&philo->states->lock);
    philo->last_eat = get_timestamp() - philo->states->start;
    printf(GREEN "%d %d is eating\n" RESET, philo->last_eat, philo->id);
    usleep(philo->states->time_to_eat);
    pthread_mutex_unlock(philo->fork_r);
    pthread_mutex_unlock(&philo->fork_l);
}

int    is_dead(t_philo *philo)
{
    printf("%d %d %d %d\n", philo->id, philo->last_eat, philo->now - philo->last_eat, philo->states->time_to_die / 1000);
    if (philo->states->someone_died)
        return (1);
    if (philo->states->someone_died || philo->now - philo->last_eat >= philo->states->time_to_die / 1000)
    {
        philo->states->someone_died = 1;
        printf(RED "%d %d died\n" RESET, philo->now, philo->id);
        return (1);
    }
    return (0);
}

int    sleep_think(t_philo *philo)
{
    pthread_mutex_lock(&philo->states->lock);
    philo->now = get_timestamp() - philo->states->start;
    if (is_dead(philo))
        return (1);
    printf(BLUE "%d %d is sleeping\n" RESET, philo->now, philo->id);
    pthread_mutex_unlock(&philo->states->lock);
    usleep(philo->states->time_to_sleep);
    pthread_mutex_lock(&philo->states->lock);
    philo->now = get_timestamp() - philo->states->start;
    if (is_dead(philo))
        return (1);
    printf(CYAN "%d %d is thinking\n" RESET, philo->now, philo->id);
    pthread_mutex_unlock(&philo->states->lock);
    return (0);
}

void    *routine(void *args)
{
    t_philo    *philo;

    philo = (t_philo *)args;
    while (1)
    {
        eat(philo);
        if (sleep_think(philo))
            break ;
        pthread_mutex_lock(&philo->states->lock);
        if (is_dead(philo))
            break ;
        pthread_mutex_unlock(&philo->states->lock);
    }
    return (NULL);
}

int    create_threads(t_states *states)
{
    int i;
    int err;

    i = 0;
    pthread_mutex_init(&states->lock, NULL);
    states->start = get_timestamp();
    while (i < states->number_philos)
    {
        if (i % 2 == 0)
        {
            states->philos[i].id = i + 1;
            err = pthread_create(&states->philos[i].thread, NULL, routine, &states->philos[i]);
            if (err)
                return (err);
            err = pthread_detach(states->philos[i].thread);
            if (err)
                return (err);
        }
        i++;
        usleep(10);
    }
    i = 0;
    while (i < states->number_philos)
    {
        if (i % 2 != 0)
        {
            states->philos[i].id = i + 1;
            err = pthread_create(&states->philos[i].thread, NULL, routine, &states->philos[i]);
            if (err)
                return (err);
            err = pthread_detach(states->philos[i].thread);
            if (err)
                return (err);
        }
        i++;
        usleep(10);
    }
    return (0);
}