/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 08:04:39 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/14 12:09:38 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief checks safely if philo's bool is set to true
/// @return 1 if dead is true 0 if dead is false
int	philo_mutex_check(t_philo *philo, int flag)
{
	bool	check;

	check = false;
	if (flag == END_M)
	{
		pthread_mutex_lock(&philo->data->end_m);
		check = philo->data->end;
		pthread_mutex_unlock(&philo->data->end_m);
	}
	else if (flag == FULL_M)
	{
		pthread_mutex_lock(&philo->full_m);
		check = philo->full;
		pthread_mutex_unlock(&philo->full_m);
	}
	else if (flag == PHILO_DEAD_M)
	{
		pthread_mutex_lock(&philo->philo_dead_m);
		check = philo->philo_dead;
		pthread_mutex_unlock(&philo->philo_dead_m);
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
			if (philo_mutex_check(&data->philo[i], FULL_M) == 1)
				j++;
			if (j == data->philos_n)
			{
				change_m_value(&data->philo[i], END_M);
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
			print_state(&data->philo[i], get_time_stamp(data), DIE);
			change_m_value(&data->philo[i], END_M);
			return (1);
		}
		i++;
	}
	return (0);
}

int	total_check(t_data *data)
{
	int		i;
	bool	check;

	i = 0;
	while (i < data->philos_n)
	{
		if (philo_mutex_check(&data->philo[i], PHILO_DEAD_M) == 1)
		{
			change_m_value(&data->philo[i], END_M);
			return (1);
		}
		i++;
	}
	pthread_mutex_lock(&data->end_m);
	check = data->end;
	pthread_mutex_unlock(&data->end_m);
	if (check == 1)
		return (1);
	if (all_full_check(data) == 1)
		return (1);
	if (time_check(data) == 1)
		return (1);
	return (0);
}
