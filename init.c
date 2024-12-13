/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 08:15:38 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/13 11:11:12 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief 
/// @param table 
/// @param i 
/// @param flag FORK_M, NUM_MEALS_M, TIME_LAST_MEAL_M
static void	destroy_failed_mutex(t_table *table, int i, int flag)
{
	pthread_mutex_destroy(&table->dead_m);
	pthread_mutex_destroy(&table->print_m);
	pthread_mutex_destroy(&table->start_m);
	while (i >= 0)
	{
		if (flag == FORK_M)
			pthread_mutex_destroy(&table->forks[i]);
		else if (flag == FULL_M)
			pthread_mutex_destroy(&table->philo[i].full_m);
		else if (flag == TIME_LAST_MEAL_M)
			pthread_mutex_destroy(&table->philo[i].time_last_meal_m);
		i--;
	}
	free(table->forks);
}

static void	init_philo_mutex(t_table *table, int i)
{
	if (pthread_mutex_init(&table->philo[i].full_m, NULL) != 0 || 
		pthread_mutex_init(&table->philo[i].time_last_meal_m, NULL) != 0)
	{
		destroy_failed_mutex(table, table->philos_n - 1, FORK_M);
		destroy_failed_mutex(table, i, FULL_M);
		destroy_failed_mutex(table, i, TIME_LAST_MEAL_M);
		free(table->philo);
		err_bye("pthread_mutex_init() failure: init_philo_mutex\n");
	}

}

static void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->philos_n);
	if (table->philo == NULL)
	{
		mutex_cleanup(table);
		err_bye("malloc failure: init_philos\n");
	}
	while (i < table->philos_n)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].time_last_meal = 0;
		table->philo[i].full = false;
		table->philo[i].table = table;
		table->philo[i].right_f = &table->forks[i];
		if (i + 1 == table->philos_n)
			table->philo[i].left_f = &table->forks[0];
		else
			table->philo[i].left_f = &table->forks[i + 1];
		init_philo_mutex(table, i);
		i++;
	}
}

static void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philos_n);
	if (table->forks == NULL)
		err_bye("malloc failure: init_forks\n");
	while (i < table->philos_n)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			destroy_failed_mutex(table, i, FORK_M);
			err_bye("pthread_mutex_init() failure: forks\n");
		}
		i++;
	}
}

void	init(t_table *table, char **argv, int argc)
{
	parse(table, argv, argc);
	table->dead = false;
	table->started = 0;
	table->dead_m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	table->print_m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	table->start_m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	init_forks(table);
	init_philos(table);
}
