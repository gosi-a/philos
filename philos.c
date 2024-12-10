/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 13:32:01 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/10 13:51:13 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	if (!arg)
		print("hello\n");
}

void	make_philos(t_table *table)
{
	int	i;
	int	check;

	i = 0;
	while (i < table->philos_num)
	{
		check = pthread_create(&table->philo[i], NULL, &routine, NULL);
		if (check != 0)
			err_clean_bye(table, "pthread_create() failure: philos");
		i++;
	}
}

void	join_philos(t_table *table)
{
	int	i;
	int	check;

	i = 0;
	while (i < table->philos_num)
	{
		check = pthread_join(&table->philo[i], NULL);
		if (check != 0)
			err_clean_bye(table, "pthread_create() failure: philos");
			i++;
	}
}