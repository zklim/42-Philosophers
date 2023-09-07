/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:53:14 by zhlim             #+#    #+#             */
/*   Updated: 2023/09/08 01:35:15 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_philo *philo)
{
	if (philo->eat_count == philo->states->times_must_eat)
	{
		sem_post(philo->states->print);
		return (1);
	}
	else if (philo->now - philo->last_eat >= philo->states->time_to_die
		|| philo->states->number_philos == 1)
	{
		sem_post(philo->states->print);
		return (1);
	}
	return (0);
}

void	ft_sem_unlink()
{
	sem_unlink("gib_fork");
	sem_unlink("dead");
	sem_unlink("print");
	sem_unlink("eat");
}

void	ft_sem_close(t_states *states)
{
	sem_close(states->forks);
	sem_close(states->dead);
	sem_close(states->print);
	sem_close(states->eats);
}
