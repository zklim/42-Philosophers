/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:03:49 by zhlim             #+#    #+#             */
/*   Updated: 2023/09/03 16:30:58 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set(t_philo *philo)
{
	philo->states->finish_eat++;
	if (philo->states->finish_eat == philo->states->number_philos)
		philo->states->someone_died = 1;
	pthread_mutex_unlock(&philo->states->lock);
}

void	set2(t_philo *philo)
{
	philo->states->someone_died = 1;
	unlock_print(philo, DIED);
}

void	*monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&philo->states->lock);
		philo->now = get_timestamp() - philo->states->start;
		if (philo->states->someone_died
			|| philo->eat_count == philo->states->times_must_eat)
		{
			set(philo);
			break ;
		}
		else if (philo->now - philo->last_eat >= philo->states->time_to_die
			|| philo->states->time_to_die < philo->states->time_to_eat
			|| philo->states->number_philos == 1)
		{
			set2(philo);
			break ;
		}
		pthread_mutex_unlock(&philo->states->lock);
		usleep(25);
	}
	return (NULL);
}
