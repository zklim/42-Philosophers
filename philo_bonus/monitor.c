/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:03:49 by zhlim             #+#    #+#             */
/*   Updated: 2023/09/06 19:04:39 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_eat(t_philo *philo)
{
	philo->states->finish_eat++;
	if (philo->states->finish_eat == philo->states->number_philos)
		// sem_post(philo->states->dead);
	sem_post(philo->states->print);
}

void	set_dead(t_philo *philo)
{
	unlock_print(philo, DIED);
	sem_post(philo->states->dead);
}

void	*monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		sem_wait(philo->states->print);
		philo->now = get_timestamp() - philo->states->start;
		if (philo->states->someone_died
			|| philo->eat_count == philo->states->times_must_eat)
		{
			set_eat(philo);
			break ;
		}
		else if (philo->now - philo->last_eat >= philo->states->time_to_die
			|| philo->states->time_to_die < philo->states->time_to_eat
			|| philo->states->number_philos == 1)
		{
			set_dead(philo);
			break ;
		}
		sem_post(philo->states->print);
		usleep(25);
	}
	return (NULL);
}
