/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 08:34:27 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/17 12:56:44 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief gets the time_stamp needed for printing the state of the philo
/// @return the time_stamp in milliseconds
long	get_time_stamp(t_data *data)
{
	return (get_time(data) - data->started);
}

/// @brief gets the number of seconds since 1st Jan 1970
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

int	ft_sleep(t_philo *philo, long sleep_time)
{
	long	start;

	start = get_time(philo->data);
	while (get_time(philo->data) - start < sleep_time)
	{
		if (bool_check(philo, PHILO_DEAD_M) == 1)
			return (-1);
		usleep(500);
	}
	return (0);
}
