/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/07 06:58:00 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/19 09:04:55 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	make_philos(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->start_m);
	while (i < data->philos_n)
	{
		if (pthread_create(&data->philo[i].th, NULL, &routine, \
			(void *)&data->philo[i]) != 0)
		{
			pthread_mutex_unlock(&data->start_m);
			err_clean_bye(data, "pthread_create() failure: philos\n", i);
			return (-1);
		}
		i++;
	}
	data->started = get_time(data);
	pthread_mutex_unlock(&data->start_m);
	monitoring(data);
	return (0);
}

static int	join_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_n)
	{
		if (pthread_join(data->philo[i].th, NULL) != 0)
		{
			err_clean_bye(data, "pthread_create() failure: philos\n", 0);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		write(2, "\033[1;31mError: \033[0m", 18);
		write(2, "invalid input: use: ./philo ", 28);
		write(2, "\033[3mnumber_of_philos time_to_die time_to_eat ", 45);
		write(2, "time_to_sleep [number_of_meals]\033[0m\n", 36);
		return (1);
	}
	if (init(&data, argv, argc) == -1)
		return (1);
	if (make_philos(&data) == -1)
		return (1);
	if (join_philos(&data) == -1)
		return (1);
	clean_bye(&data);
	return (0);
}
