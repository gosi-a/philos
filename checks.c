/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 08:04:39 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/13 14:37:41 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief checks safely if philo's bool is set to true
/// @return 1 if dead is true 0 if dead is false
int	philo_mutex_check(t_data *data, t_philo *philo, int flag)
{
	bool	check;

	check = false;
	if (flag == DEAD_M)
	{
		pthread_mutex_lock(&data->dead_m);
		check = data->dead;
		pthread_mutex_unlock(&data->dead_m);
	}
	else if (flag == FULL_M)
	{
		pthread_mutex_lock(&philo->full_m);
		check = philo->full;
		pthread_mutex_unlock(&philo->full_m);
	}
	if (check == false)
		return (0);
	return (1);
}

long	philos_mutex_long_check(t_philo *philo)
{
	long	check;

	pthread_mutex_lock(&philo->time_last_meal_m);
	check = philo->time_last_meal;
	pthread_mutex_unlock(&philo->time_last_meal_m);
	return (check);
}

static int	full_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (data->meals != -1)
	{
		while (i < data->philos_n)
		{
			if (philo_mutex_check(data, &data->philo[i], FULL_M) == 1)
				j++;
			if (j == data->philos_n)
			{
				change_m_value(data, &data->philo[i], DEAD_M);
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
	long	check;

	i = 0;
	while (i < data->philos_n)
	{
		check = philos_mutex_long_check(&data->philo[i]);
		if (get_time(data) - check >= data->tt_die)
		{
			print_state(data, get_time_stamp(data), data->philo[i].id, DIE);
			return (1);
		}
		i++;
	}
	return (0);
}

int	total_check(t_data *data)
{
	if (philo_mutex_check(data, data->philo, DEAD_M) == 1)
		return (1);
	if (full_check(data) == 1)
		return (1);
	if (time_check(data) == 1)
		return (1);
	return (0);
}
