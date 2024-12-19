/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 08:15:38 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/19 08:27:56 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief destroys already created mutexes in case of mutex_init() failure
/// @param i number of already created mutexes
/// @param flag FORK_M, NUM_MEALS_M, TIME_LAST_MEAL_M
static void	destroy_failed_mutex(t_data *data, int i, int flag)
{
	pthread_mutex_destroy(&data->print_m);
	pthread_mutex_destroy(&data->start_m);
	while (i >= 0)
	{
		if (flag == FORK_M)
			pthread_mutex_destroy(&data->forks[i]);
		else if (flag == FULL_M)
			pthread_mutex_destroy(&data->philo[i].full_m);
		else if (flag == TIME_LAST_MEAL_M)
			pthread_mutex_destroy(&data->philo[i].time_last_meal_m);
		i--;
	}
	free(data->forks);
}

static int	init_philo_mutex(t_data *data, int i)
{
	data->philo[i].right_f = &data->forks[i];
	if (data->philo[i].id == data->philos_n)
		data->philo[i].left_f = &data->forks[0];
	else
		data->philo[i].left_f = &data->forks[i + 1];
	if (pthread_mutex_init(&data->philo[i].full_m, NULL) != 0
		|| pthread_mutex_init(&data->philo[i].time_last_meal_m, NULL) != 0
		|| pthread_mutex_init(&data->philo[i].philo_dead_m, NULL) != 0)
	{
		destroy_failed_mutex(data, data->philos_n - 1, FORK_M);
		destroy_failed_mutex(data, i, FULL_M);
		destroy_failed_mutex(data, i, TIME_LAST_MEAL_M);
		free(data->philo);
		err_bye("pthread_mutex_init() failure: init_philo_mutex\n");
		return (-1);
	}
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->philos_n);
	if (data->philo == NULL)
	{
		mutex_cleanup(data);
		err_bye("malloc failure: init_philos\n");
	}
	while (i < data->philos_n)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].time_last_meal = 0;
		data->philo[i].full = false;
		data->philo[i].philo_dead = false;
		data->philo[i].data = data;
		if (init_philo_mutex(data, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_n);
	if (data->forks == NULL)
	{
		err_bye("malloc failure: init_forks\n");
		return (-1);
	}
	while (i < data->philos_n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			destroy_failed_mutex(data, i, FORK_M);
			err_bye("pthread_mutex_init() failure: forks\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init(t_data *data, char **argv, int argc)
{
	if (parse(data, argv, argc) == -1)
		return (-1);
	data->started = 0;
	data->print_m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	data->start_m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	if (init_forks(data) == -1)
		return (-1);
	if (init_philos(data) == -1)
		return (-1);
	return (0);
}
