/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:16:06 by zhlim             #+#    #+#             */
/*   Updated: 2023/09/02 17:55:33 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo *philos)
{
	free(philos);
}

int	free_forks(t_states *states, int end)
{
	int	i;
	int	err;

	i = 0;
	while (i < end)
	{
		err = pthread_mutex_destroy(&states->philos[i].fork_l);
		if (err)
			return (err);
		i++;
	}
	return (0);
}

int	ft_free(t_states *states)
{
	int	err;

	err = 0;
	err = pthread_mutex_destroy(&states->lock);
	if (err)
		return (err);
	err = free_forks(states, states->number_philos);
	if (err)
		return (err);
	free_philo(states->philos);
	return (err);
}
