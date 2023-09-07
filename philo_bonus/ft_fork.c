/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:20:36 by zhlim             #+#    #+#             */
/*   Updated: 2023/09/08 01:50:57 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_exit(int i)
{
	// system("leaks -q philo_bonus");
	exit(i);
}

void	take_fork(t_philo *philo)
{
	sem_wait(philo->states->forks);
	sem_wait(philo->states->print);
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
	{
		sem_post(philo->states->forks);
		sem_close(philo->states->forks);
		ft_exit(0);
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
		ft_exit(0);
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
		ft_exit(0);
	unlock_print(philo, SLEEP);
	ft_usleep(philo->states->time_to_sleep);
	sem_wait(philo->states->print);
	philo->now = get_timestamp() - philo->states->start;
	if (is_dead(philo))
		ft_exit(0);
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

void	sem_eat(t_states *states)
{
	int			i;

	i = 0;
	while(i < states->number_philos)
	{
		sem_wait(states->eats);
		i++;
	}
	sem_post(states->dead);
	ft_exit(0);
}

void	ft_fork(t_states *states)
{
	int	i;

	i = 0;
	states->start = get_timestamp();
	while (i < states->number_philos)
	{
		states->philos[i].id = i + 1;
		states->philos[i].pid = fork();
		if (states->philos[i].pid == 0)
			routine(&states->philos[i]);
		i++;
		usleep(50);
	}
	i = 0;
	if (states->philos[i].pid != 0)
	{
		usleep(800);
		if (states->times_must_eat > 0)
		{
			states->sem_eat = fork();
			if (states->sem_eat == 0)
				sem_eat(states);
		}
		sem_wait(states->dead);
		while (i < states->number_philos)
		{
			kill(states->philos[i].pid, SIGTERM);
			waitpid(states->philos[i].pid, NULL, 0);
			i++;
		}
		if (states->times_must_eat > 0)
		{
			kill(states->sem_eat, SIGTERM);
			waitpid(states->sem_eat, NULL, 0);
		}
		ft_sem_close(states);
		ft_sem_unlink();
	}
}

// void	ft_fork(t_states *states)
// {
// 	(void)states;
// 	ft_sem_unlink();
// }