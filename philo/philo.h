/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:50:15 by zhlim             #+#    #+#             */
/*   Updated: 2023/09/10 17:09:36 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\x1B[0m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"

# define FORK 0
# define FORK2 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIED 5

typedef struct s_local_p
{
	int				i;
	int				now;
	int				times_must_eat;
	int				time_to_die;
	int				number_philos;
}					t_local_p;

typedef struct s_local_c
{
	int				eat_time;
	int				sleep_time;
	int				start;
	int				now;
	int				number_philos;
}					t_local_c;

typedef struct s_philo
{
	int				id;
	int				last_eat;
	int				eat_count;
	int				recorded;
	pthread_t		thread;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	*fork_r;
	struct s_states	*states;
}					t_philo;

typedef struct s_states
{
	int				number_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				someone_died;
	int				finish_eat;
	long			start;
	t_philo			*philos;
	pthread_mutex_t	lock;
	pthread_mutex_t	print;
}					t_states;

int					create_philo(t_states *states);
void				free_philo(t_philo *philos);
int					create_threads(t_states *states);
int					create_forks(t_states *states);
int					ft_free(t_states *states);
int					free_forks(t_states *states, int end);
void				ft_print(t_philo *philo, int type, int now);
void				ft_usleep(int i);
long				get_timestamp(void);
int					nbr_ft(const char *str, int sign);
int					ft_atoi(const char *str);
int					is_dead(t_philo *philo);

#endif