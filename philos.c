/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 13:32:01 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/12 09:12:37 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*go(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	return (NULL);
}

void	make_philos(t_table *table)
{
	int	i;
	int	chck;

	i = 0;
	table->started = get_time(table);
	while (i < table->philos_n)
	{
		chck = pthread_create(&table->philo[i].th, NULL, &go, \
			(void *)&table->philo[i]);
		if (chck != 0)
			err_clean_bye(table, "pthread_create() failure: philos\n", i);
		i++;
	}
}

void	join_philos(t_table *table)
{
	int	i;
	int	check;

	i = 0;
	while (i < table->philos_n)
	{
		check = pthread_join(table->philo[i].th, NULL);
		if (check != 0)
			err_clean_bye(table, "pthread_create() failure: philos\n", 0);
		i++;
	}
}
