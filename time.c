/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 08:34:27 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/13 13:07:00 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief makes sure that all threads start together (no barrier allowed)
void	thread_synch(t_table *table)
{
	pthread_mutex_lock(&table->start_m);
	pthread_mutex_unlock(&table->start_m);
}

/// @brief gets the time_stamp needed for printing the state of the philo
/// @return the time_stamp in milliseconds
long	get_time_stamp(t_table *table)
{
	long	now;

	now = get_time(table);
	return (now - table->started);
}

/// @brief gets the number of seconds (in milliseconds) since 1st Jan 1970
/// @return the number of seconds (in milliseconds)
long	get_time(t_table *table)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) != 0)
		err_clean_bye(table, "gettimeofday() failure\n", table->philos_n - 1);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

/// @brief updated usleep version, also checks if philos died
/// @param table data
/// @param time_len length of time philos should sleep/wait
/// @param philo_id philo's id (in case of death & print)
void	ft_sleep(t_table *table, long sleep_time, int id)
{
	long	now;
	long	last_meal;

	last_meal = philos_mutex_long_check(&table->philo[id - 1]);
	now = get_time(table);
	while (get_time(table) - now < sleep_time &&
		philo_mutex_check(table, &table->philo[id - 1], DEAD_M) == 0)
	{
		if (get_time(table) - last_meal >= table->tt_die)
			print_state(table, get_time_stamp(table), id, DIE);
		if (philo_mutex_check(table, &table->philo[id - 1], DEAD_M) == 1)
			break ;
		usleep(100);
	}
}
