/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:20:36 by zhlim             #+#    #+#             */
/*   Updated: 2023/09/05 18:14:04 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// int	take_fork(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->fork_l);
// 	pthread_mutex_lock(&philo->states->lock);
// 	philo->now = get_timestamp() - philo->states->start;
// 	if (is_dead(philo))
// 	{
// 		pthread_mutex_unlock(&philo->fork_l);
// 		return (1);
// 	}
// 	unlock_print(philo, FORK);
// 	return (0);
// }

// int	eat(t_philo *philo)
// {
// 	if (take_fork(philo))
// 		return (1);
// 	pthread_mutex_lock(philo->fork_r);
// 	pthread_mutex_lock(&philo->states->lock);
// 	philo->now = get_timestamp() - philo->states->start;
// 	if (is_dead(philo))
// 	{
// 		pthread_mutex_unlock(philo->fork_r);
// 		pthread_mutex_unlock(&philo->fork_l);
// 		return (1);
// 	}
// 	unlock_print(philo, FORK2);
// 	pthread_mutex_lock(&philo->states->lock);
// 	philo->last_eat = get_timestamp() - philo->states->start;
// 	unlock_print(philo, EAT);
// 	ft_usleep(philo->states->time_to_eat);
// 	pthread_mutex_unlock(philo->fork_r);
// 	pthread_mutex_unlock(&philo->fork_l);
// 	return (0);
// }

// int	sleep_think(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->states->lock);
// 	philo->now = get_timestamp() - philo->states->start;
// 	if (is_dead(philo))
// 		return (1);
// 	unlock_print(philo, SLEEP);
// 	ft_usleep(philo->states->time_to_sleep);
// 	pthread_mutex_lock(&philo->states->lock);
// 	philo->now = get_timestamp() - philo->states->start;
// 	if (is_dead(philo))
// 		return (1);
// 	unlock_print(philo, THINK);
// 	return (0);
// }

// void	*routine(void *args)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)args;
// 	if (!(philo->id % 2))
// 		usleep(1000);
// 	pthread_create(&philo->monitor, NULL, monitor, philo);
// 	pthread_detach(philo->monitor);
// 	while (1)
// 	{
// 		if (eat(philo))
// 			break ;
// 		if (sleep_think(philo))
// 			break ;
// 	}
// 	return (NULL);
// }

// int	create_threads(t_states *states)
// {
// 	int	i;
// 	int	err;

// 	i = 0;
// 	states->start = get_timestamp();
// 	while (i < states->number_philos)
// 	{
// 		states->philos[i].id = i + 1;
// 		err = pthread_create(&states->philos[i].thread, NULL, routine,
// 				&states->philos[i]);
// 		if (err)
// 			return (err);
// 		i++;
// 		usleep(25);
// 	}
// 	while (!states->someone_died)
// 		;
// 	return (0);
// }

void	ft_sem(t_philo *philo)
{
	sem_wait(philo->states->forks);
	printf("%d\n", philo->id);
	usleep(1000000);
	sem_post(philo->states->forks);
	sem_close(philo->states->forks);
	exit(0);
}

void	ft_fork(t_states *states)
{
	int	i;

	i = 0;
	while (i < states->number_philos)
	{
		states->philos[i].id = i + 1;
		states->philos[i].pid = fork();
		if (states->philos[i].pid == 0)
			ft_sem(&states->philos[i]);
		else
			printf("parent\n");
		i++;
	}
	i = 0;
	if (states->philos[i].pid != 0)
	{
		while (i < states->number_philos)
		{
			waitpid(states->philos[i].pid, NULL, 0);
			i++;
		}
		sem_close(states->forks);
		sem_unlink("gib_fork");
	}
}
