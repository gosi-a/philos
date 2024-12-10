/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 08:15:38 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/10 12:08:50 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_failed_mutex(t_table *table, int i)
{
	pthread_mutex_destroy(&table->began_m);
	pthread_mutex_destroy(&table->dead_m);
	pthread_mutex_destroy(&table->meal_m);
	pthread_mutex_destroy(&table->print_m);
	while (i >= 0)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i--;
	}
	free(table->forks);
}

static void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->philos_num);
	if (table->philo == NULL)
	{
		mutex_cleanup(table);
		err_bye("malloc failure: init_philos");
	}
	while (i < table->philos_num)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].time_last_meal = 0;
		table->philo[i].table = table;
		table->philo[i].right_f = &table->forks[i];
		if (i + 1 == table->philos_num)
			table->philo[i].left_f = &table->forks[0];
		else
			table->philo[i].left_f = &table->forks[i + 1];
		i++;
	}
}

static void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philos_num);
	if (table->forks == NULL)
		err_bye("malloc failure: init_forks");
	while (i < table->philos_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			destroy_failed_mutex(table, i);
			err_bye("pthread_mutex_init() failure: forks");
		}
		i++;
	}
}

void	init(t_table *table, char **argv, int argc)
{
	parse(table, argv, argc);
	table->dead = false;
	table->started = 0;
	table->began_m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	table->dead_m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	table->meal_m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	table->print_m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	init_forks(table);
	init_philos(table);
}
