/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 08:04:39 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/17 10:56:20 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_last_meal_m);
	if (philo->data->tt_die <= get_time(philo->data) - philo->time_last_meal)
	{
		pthread_mutex_lock(&philo->philo_dead_m);
		philo->philo_dead = true;
		pthread_mutex_unlock(&philo->philo_dead_m);
		pthread_mutex_unlock(&philo->time_last_meal_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->time_last_meal_m);
	return (0);
}

static void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_n)
	{
		pthread_mutex_lock(&data->philo[i].philo_dead_m);
		data->philo[i].philo_dead = true;
		pthread_mutex_unlock(&data->philo[i].philo_dead_m);
		i++;
	}
}

static int	all_full_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (data->meals != -1)
	{
		while (i < data->philos_n)
		{
			if (bool_check(&data->philo[i], FULL_M) == 1)
				j++;
			if (j == data->philos_n)
			{
				kill_all(data);
				pthread_mutex_lock(&data->print_m);
				pthread_mutex_unlock(&data->print_m);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

void	monitoring(t_data *data)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < data->philos_n)
		{
			if (is_alive(&data->philo[i]) == 1)
			{
				kill_all(data);
				pthread_mutex_lock(&data->print_m);
				printf("%zu\t%d died\n", \
					get_time_stamp(data), data->philo[i].id);
				pthread_mutex_unlock(&data->print_m);
				return ;
			}
			i++;
		}
		if (all_full_check(data) == 1)
			return (1);
		usleep (100);
	}
	return (0);
}
