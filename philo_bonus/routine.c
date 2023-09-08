/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:00:12 by zhlim             #+#    #+#             */
/*   Updated: 2023/09/08 14:00:26 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_fork(t_philo *philo)
{
	sem_wait(philo->states->forks);
	sem_wait(philo->states->print);
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
	{
		sem_post(philo->states->forks);
		sem_close(philo->states->forks);
		exit(0);
	}
	unlock_print(philo, FORK);
}

void	eat(t_philo *philo)
{
	take_fork(philo);
	sem_wait(philo->states->forks);
	sem_wait(philo->states->print);
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
	{
		sem_post(philo->states->forks);
		sem_post(philo->states->forks);
		sem_close(philo->states->forks);
		exit(0);
	}
	unlock_print(philo, FORK2);
	sem_wait(philo->states->print);
	philo->last_eat = get_timestamp() - philo->states->start;
	unlock_print(philo, EAT);
	ft_usleep(philo->states->time_to_eat);
	sem_post(philo->states->forks);
	sem_post(philo->states->forks);
}

int	sleep_think(t_philo *philo)
{
	sem_wait(philo->states->print);
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
		exit(0);
	unlock_print(philo, SLEEP);
	ft_usleep(philo->states->time_to_sleep);
	sem_wait(philo->states->print);
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
		exit(0);
	unlock_print(philo, THINK);
	return (0);
}

void	routine(t_philo *philo)
{
	if (philo->states->times_must_eat > 0)
		sem_wait(philo->states->eats);
	sem_wait(philo->states->dead);
	pthread_create(&philo->monitor, NULL, monitor, philo);
	pthread_detach(philo->monitor);
	while (1)
	{
		eat(philo);
		sleep_think(philo);
	}
}
