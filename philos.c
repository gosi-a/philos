/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 13:32:01 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/12 12:30:41 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_and_only(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	philo->time_last_meal = get_time(table);
	pthread_mutex_lock(philo->right_f);
	print_state(table, get_time_stamp(table), philo->id, FORK);
	while (1)
	{
		if (get_time(table) - table->started >= table->tt_die)
		{
			print_state(table, get_time_stamp(table), philo->id, DIE);
			break ;
		}
	}
	pthread_mutex_unlock(philo->right_f);
}

void	*go(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (table->philos_n == 1)
		one_and_only(philo);
	else
	{
		if (philo->id % 2 != 0)
			ft_sleep(table, 200, philo->id);
		philo->time_last_meal = get_time(table);
		pthread_mutex_lock(philo->right_f);
		print_state(table, get_time_stamp(table), philo->id, FORK);
		pthread_mutex_lock(philo->left_f);
		print_state(table, get_time_stamp(table), philo->id, FORK);
		print_state(table, get_time_stamp(table), philo->id, EAT);
		ft_sleep(table, table->tt_eat, philo->id);
		philo->time_last_meal = get_time(table);
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
		print_state(table, get_time_stamp(table), philo->id, SLEEP);
		ft_sleep(table, get_time_stamp(table), philo->id);
		print_state(table, get_time_stamp(table), philo->id, THINK);
	}
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
