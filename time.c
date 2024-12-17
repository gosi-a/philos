/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 08:34:27 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/17 09:17:12 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief gets the time_stamp needed for printing the state of the philo
/// @return the time_stamp in milliseconds
long	get_time_stamp(t_data *data)
{
	long	now;

	now = get_time(data);
	if (now == -1)
		return (now);
	return (now - data->started);
}

/// @brief gets the number of seconds (in milliseconds) since 1st Jan 1970
/// @return the number of seconds (in milliseconds)
long	get_time(t_data *data)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) != 0)
	{
		err_clean_bye(data, "gettimeofday() failure\n", data->philos_n - 1);
		return (-1);
	}
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

/// @brief updated usleep version, also checks if philos died
/// @param data data
/// @param time_len length of time philos should sleep/wait
int	ft_sleep(t_philo *philo, long sleep_time)
{
	long	start;
	long	end;

	start = get_time(philo->data);
	end = start + sleep_time;
	while (start < end)
	{
		if (bool_check(philo, PHILO_DEAD_M) == 1)
			return (-1);
		usleep(50);
		start = get_time(philo->data);
	}
	return (0);
}
