/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 08:34:27 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/14 12:12:01 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief makes sure that all threads start together (no barrier allowed)
void	thread_synch(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->start_m);
	pthread_mutex_unlock(&philo->data->start_m);
}

/// @brief gets the time_stamp needed for printing the state of the philo
/// @return the time_stamp in milliseconds
long	get_time_stamp(t_data *data)
{
	long	now;

	now = get_time(data);
	return (now - data->started);
}

/// @brief gets the number of seconds (in milliseconds) since 1st Jan 1970
/// @return the number of seconds (in milliseconds)
long	get_time(t_data *data)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) != 0)
		err_clean_bye(data, "gettimeofday() failure\n", data->philos_n - 1);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

/// @brief updated usleep version, also checks if philos died
/// @param data data
/// @param time_len length of time philos should sleep/wait
/// @param philo_id philo's id (in case of death & print)
void	ft_sleep(t_philo *philo, long sleep_time)
{
	int		id;
	long	now;
	long	last_meal;
	t_data	*data;

	id = philo->id;
	data = philo->data;
	last_meal = philos_mutex_long_check(philo);
	now = get_time(philo->data);
	while (get_time(philo->data) - now < sleep_time
		&& philo_mutex_check(philo, END_M) == 0)
	{
		if (get_time(philo->data) - last_meal >= philo->data->tt_die)
			print_state(philo, get_time_stamp(data), DIE);
		if (philo_mutex_check(philo, END_M) == 1)
			break ;
		usleep(100);
	}
}
