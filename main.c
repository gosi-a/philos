/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/07 06:58:00 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/12 08:58:50 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table table;
	if (argc < 5 || argc > 6)
	{
		write(2, "\033[1;31mError: \033[0m", 18);
		write(2, "invalid input: use: ./philo ", 28);
		write(2, "\033[3mnumber_of_philos time_to_die time_to_eat ", 45);
		write(2, "time_to_sleep [number_of_meals]\033[0m\n", 36);
		return (1);
	}
	init(&table, argv, argc);
	clean_bye(&table);
	return (0);
}

// valgrind --tool=helgrind ./philo ...