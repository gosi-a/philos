/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 08:04:39 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/13 11:10:27 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief checks safely if philo's bool is set to true
/// @return 1 if dead is true 0 if dead is false
int	philo_mutex_check(t_table *table, t_philo *philo, int flag)
{
	bool	check;

	check = false;
	if (flag == DEAD_M)
	{
		pthread_mutex_lock(&table->dead_m);
		check = table->dead;
		pthread_mutex_unlock(&table->dead_m);
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

static int	full_check(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (table->meals != -1)
	{
		while (i < table->philos_n)
		{
			if (philo_mutex_check(table, &table->philo[i], FULL_M) == 1)
				j++;
			if (j == table->philos_n)
			{
				change_m_value(table, &table->philo[i], DEAD_M);
				return (1);
			}	
			i++;
		}
	}
	return (0);
}

static int	time_check(t_table *table)
{
	int		i;
	long	check;
	
	i = 0;
	while (i < table->philos_n)
	{
		check = philos_mutex_long_check(&table->philo[i]);
		if (get_time(table) - check >= table->tt_die)
		{
			print_state(table, get_time_stamp(table), table->philo[i].id, DIE);
			return (1);
		}
		i++;
	}
	return (0);
}

int	total_check(t_table *table)
{
	if (philo_mutex_check(table, table->philo, DEAD_M) == 1)
		return (1);
	if (full_check(table) == 1)
		return (1);
	if (time_check(table) == 1)
		return (1);
	return (0);
}

