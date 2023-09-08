/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:20:36 by zhlim             #+#    #+#             */
/*   Updated: 2023/09/08 17:42:39 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l);
	pthread_mutex_lock(&philo->states->lock);
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->fork_l);
		return (1);
	}
	unlock_print(philo, FORK);
	if (philo->states->number_philos == 1)
	{
		while (1)
		{
			pthread_mutex_lock(&philo->states->lock);
			if (is_dead(philo))
			{
				pthread_mutex_unlock(&philo->fork_l);
				return (1);
			}
			pthread_mutex_unlock(&philo->states->lock);
			usleep(25);
		}
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (take_fork(philo))
		return (1);
	pthread_mutex_lock(philo->fork_r);
	pthread_mutex_lock(&philo->states->lock);
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(&philo->fork_l);
		return (1);
	}
	unlock_print(philo, FORK2);
	pthread_mutex_lock(&philo->states->lock);
	philo->last_eat = get_timestamp() - philo->states->start;
	unlock_print(philo, EAT);
	ft_usleep(philo->states->time_to_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(&philo->fork_l);
	return (0);
}

int	sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->states->lock);
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
		return (1);
	unlock_print(philo, SLEEP);
	ft_usleep(philo->states->time_to_sleep);
	pthread_mutex_lock(&philo->states->lock);
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
		return (1);
	unlock_print(philo, THINK);
	return (0);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (!(philo->id % 2))
		usleep(1000);
	pthread_create(&philo->monitor, NULL, monitor, philo);
	pthread_detach(philo->monitor);
	while (1)
	{
		if (eat(philo))
			break ;
		if (sleep_think(philo))
			break ;
	}
	return (NULL);
}

int	create_threads(t_states *states)
{
	int	i;
	int	err;

	i = 0;
	states->start = get_timestamp();
	while (i < states->number_philos)
	{
		states->philos[i].id = i + 1;
		err = pthread_create(&states->philos[i].thread, NULL, routine,
				&states->philos[i]);
		err = pthread_detach(states->philos[i].thread);
		if (err)
			return (err);
		i++;
		usleep(25);
	}
	return (0);
}
