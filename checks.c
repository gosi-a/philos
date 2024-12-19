/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 08:04:39 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/19 10:15:58 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	is_alive(t_data *data, int i)
{
	pthread_mutex_lock(&data->philo[i].time_last_meal_m);
	if (data->philo[i].time_last_meal > 0 \
		&& data->tt_die < get_time(data) - data->philo[i].time_last_meal)
	{
		pthread_mutex_unlock(&data->philo[i].time_last_meal_m);
		kill_all(data);
		pthread_mutex_lock(&data->print_m);
		printf(GREEN"%zu"R"\t%d "RED"died"R"\n", \
			get_time_stamp(data), data->philo[i].id);
		pthread_mutex_unlock(&data->print_m);
		return (1);
	}
	pthread_mutex_unlock(&data->philo[i].time_last_meal_m);
	return (0);
}

void	monitoring(t_data *data)
{
	int	i;
	int	j;

	while (1)
	{
		i = 0;
		j = 0;
		while (i < data->philos_n)
		{
			if (is_alive(data, i) == 1)
				return ;
			if (data->meals != -1)
			{
				if (bool_check(&data->philo[i], FULL_M) == 1)
					j++;
				if (j == data->philos_n)
					return ;
			}
			i++;
		}
		usleep (100);
	}
}
