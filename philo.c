/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:50:02 by zhlim             #+#    #+#             */
/*   Updated: 2023/08/24 17:57:41 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	nbr_ft(const char *str, int sign)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str++ - '0');
		i++;
		if (i >= 20 && sign > 0)
			return (-1);
		else if (i >= 20 && sign < 0)
			return (0);
	}
	return (res * sign);
}

int	ft_atoi(const char *str)
{
	int	sign;

	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	return (nbr_ft(str, sign));
}

void	assignment(char **av, t_states *states)
{
	states->number_philos = ft_atoi(*av);
	states->time_to_die = ft_atoi(*(av + 1));
	states->time_to_eat = ft_atoi(*(av + 2));
	states->time_to_sleep = ft_atoi(*(av + 3));
	if (*(av + 4))
		states->times_must_eat = ft_atoi(*(av + 4));
	else
		states->times_must_eat = -1;
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

int	main(int ac, char **av)
{
	t_states    states;

	if (invalidate(ac, av + 1))
		return (1);
	assignment(av + 1, &states);
    if (create_philo(&states))
        return (1);
}