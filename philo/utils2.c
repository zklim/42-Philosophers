/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:53:14 by zhlim             #+#    #+#             */
/*   Updated: 2023/09/08 16:50:41 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	if (philo->states->someone_died
		|| philo->eat_count == philo->states->times_must_eat)
	{
		pthread_mutex_unlock(&philo->states->lock);
		return (1);
	}
	else if (philo->now - philo->last_eat >= philo->states->time_to_die)
	{
		pthread_mutex_unlock(&philo->states->lock);
		return (1);
	}
	return (0);
}
