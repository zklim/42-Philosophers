/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:50:02 by zhlim             #+#    #+#             */
/*   Updated: 2023/09/05 18:11:44 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_states(char **av, t_states *states)
{
	states->number_philos = ft_atoi(*av);
	states->time_to_die = ft_atoi(*(av + 1));
	states->time_to_eat = ft_atoi(*(av + 2));
	states->time_to_sleep = ft_atoi(*(av + 3));
	if (*(av + 4))
		states->times_must_eat = ft_atoi(*(av + 4));
	else
		states->times_must_eat = -1;
	states->someone_died = 0;
	states->finish_eat = 0;
	pthread_mutex_init(&states->lock, NULL);
	states->forks = sem_open("gib_fork", O_CREAT, 0644, states->number_philos);
}

int	invalidate(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ac < 5 || ac > 6)
		return (1);
	while (av[i])
	{
		while (av[i][j])
		{
			if (av[i][j] < '0' && av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	join(t_states *states)
{
	int	i;
	int	err;

	i = 0;
	while (i < states->number_philos)
	{
		err = pthread_join(states->philos[i].thread, NULL);
		if (err)
			return (err);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_states	states;

	if (invalidate(ac, av + 1))
		return (1);
	init_states(av + 1, &states);
	if (create_philo(&states))
		return (1);
	ft_fork(&states);
	return (0);
}