/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/07 06:58:00 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/13 13:31:18 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	make_philos(t_table *table)
{
	int	i;

	i = 0;
	table->started = get_time(table);
	pthread_mutex_lock(&table->start_m);
	while (i < table->philos_n)
	{
		if (pthread_create(&table->philo[i].th, NULL, &routine, \
			(void *)&table->philo[i]) != 0)
		{
			pthread_mutex_unlock(&table->start_m);
			err_clean_bye(table, "pthread_create() failure: philos\n", i);
		}
		i++;
	}
	pthread_mutex_unlock(&table->start_m);
	usleep(2000);
	while (1)
	{
		if (total_check(table) == 1)
			break ;
		usleep(100);
	}
}

static void	join_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_n)
	{
		if (pthread_join(table->philo[i].th, NULL) != 0)
			err_clean_bye(table, "pthread_create() failure: philos\n", 0);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		write(2, "\033[1;31mError: \033[0m", 18);
		write(2, "invalid input: use: ./philo ", 28);
		write(2, "\033[3mnumber_of_philos time_to_die time_to_eat ", 45);
		write(2, "time_to_sleep [number_of_meals]\033[0m\n", 36);
		return (1);
	}
	init(&table, argv, argc);
	make_philos(&table);
	join_philos(&table);
	clean_bye(&table);
	return (0);
}

// valgrind --tool=helgrind ./philo ...