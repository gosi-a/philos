/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 08:04:39 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/16 13:18:00 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief checks safely if philo's bool is set to true
/// @return 1 if dead is true 0 if dead is false
int	philo_value_m_check(t_philo *philo, int flag)
{
	if (flag == FULL_M)
	{
		pthread_mutex_lock(&philo->full_m);
		if (philo->full == true)
		{
			pthread_mutex_unlock(&philo->full_m);
			return (1);
		}
		pthread_mutex_unlock(&philo->full_m);
	}
	else if (flag == PHILO_DEAD_M)
	{
		pthread_mutex_lock(&philo->philo_dead_m);
		if (philo->philo_dead == true)
		{
			pthread_mutex_unlock(&philo->philo_dead_m);
			return (1);
		}
		pthread_mutex_unlock(&philo->philo_dead_m);
	}
	return (0);
}

long	philos_mutex_long_check(t_philo *philo)
{
	long	check;

	pthread_mutex_lock(&philo->time_last_meal_m);
	check = philo->time_last_meal;
	pthread_mutex_unlock(&philo->time_last_meal_m);
	return (check);
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
			if (philo_value_m_check(&data->philo[i], FULL_M) == 1)
				j++;
			if (j == data->philos_n)
			{
				kill_all(data);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

static int	time_check(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philos_n)
	{
		if (is_alive(&data->philo[i]) == 1)
		{
			kill_all(data); //
			pthread_mutex_lock(&data->print_m);
			printf(GRN"%zu"R"\t%d "RED"died\n"R, get_time_stamp(data), data->philo[i].id);
			pthread_mutex_unlock(&data->print_m);
			return (1);
		}
		i++;
	}
	return (0);
}

int	total_check(t_data *data)
{
	if (time_check(data) == 1)
	{
		printf("in time_check == 1\n");
		return (1);
	}
	if (all_full_check(data) == 1)
		return (1);
	return (0);
}
