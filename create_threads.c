/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:20:36 by zhlim             #+#    #+#             */
/*   Updated: 2023/09/01 18:14:37 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->states->lock_died);
	if (philo->states->someone_died
		|| philo->eat_count == philo->states->times_must_eat)
	{
		pthread_mutex_unlock(&philo->states->lock_died);
		return (1);
	}
	else if (philo->now - philo->last_eat >= philo->states->time_to_die
		|| philo->states->time_to_die < philo->states->time_to_eat
		|| philo->states->number_philos == 1)
	{
		pthread_mutex_unlock(&philo->states->lock_died);
		return (1);
	}
	pthread_mutex_unlock(&philo->states->lock_died);
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l);
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->fork_l);
		return (1);
	}
	lock_print(philo, FORK);
	pthread_mutex_lock(philo->fork_r);
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(&philo->fork_l);
		return (1);
	}
	lock_print(philo, FORK2);
	philo->last_eat = get_timestamp() - philo->states->start;
	lock_print(philo, EAT);
	ft_usleep(philo->states->time_to_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(&philo->fork_l);
	return (0);
}

int	sleep_think(t_philo *philo)
{
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
		return (1);
	lock_print(philo, SLEEP);
	ft_usleep(philo->states->time_to_sleep);
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
		return (1);
	lock_print(philo, THINK);
	return (0);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (!(philo->id % 2))
		usleep(philo->states->time_to_eat);
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
	while (i < states->number_philos)
	{
		states->philos[i].id = i + 1;
		err = pthread_create(&states->philos[i].thread, NULL, routine,
				&states->philos[i]);
		if (err)
			return (err);
		i++;
	}
	while (!states->someone_died)
		;
	return (0);
}
