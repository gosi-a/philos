/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 13:32:01 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/13 13:49:18 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_and_only(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(philo->right_f);
	print_state(table, get_time_stamp(table), philo->id, FORK);
	ft_sleep(table, table->tt_die, philo->id);
	print_state(table, get_time_stamp(table), philo->id, DIE);
	pthread_mutex_unlock(philo->right_f);
}

static void	eat(t_table *table, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_f);
		print_state(table, get_time_stamp(table), philo->id, FORK);
		pthread_mutex_lock(philo->right_f);
		print_state(table, get_time_stamp(table), philo->id, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_f);
		print_state(table, get_time_stamp(table), philo->id, FORK);
		pthread_mutex_lock(philo->left_f);
		print_state(table, get_time_stamp(table), philo->id, FORK);
	}
	change_m_value(table, philo, TIME_LAST_MEAL_M);
	print_state(table, get_time_stamp(table), philo->id, EAT);
	if (table->meals != -1)
	{
		philo->meals_eaten += 1;
		if (philo->meals_eaten == table->meals)
			change_m_value(table, philo, FULL_M);
	}
	ft_sleep(table, table->tt_eat, philo->id);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

static void	more_and_more(t_philo *philo, t_table *table)
{
	long	think_time;
	eat(table, philo);
	print_state(table, get_time_stamp(table), philo->id, SLEEP);
	ft_sleep(table, table->tt_sleep, philo->id);
	print_state(table, get_time_stamp(table), philo->id, THINK);
	if (table->philos_n % 2 != 0)
	{
		think_time = table->tt_eat * 2 - table->tt_sleep;
		if (think_time > 0)
			ft_sleep(table, think_time, philo->id);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	thread_synch(philo->table);
	change_m_value(philo->table, philo, TIME_LAST_MEAL_M);
	if (philo->table->philos_n == 1)
		one_and_only(philo);
	else
	{
		if (philo->id % 2 == 0)
		{
			print_state(philo->table, get_time_stamp(philo->table), \
				philo->id, THINK);
			ft_sleep(philo->table, philo->table->tt_eat / 2, philo->id);
			if (philo_mutex_check(philo->table, philo, DEAD_M) == 1)
				return (NULL);
		}
		while (philo_mutex_check(philo->table, philo, DEAD_M) == 0)
		{
			if (philo_mutex_check(philo->table, philo, FULL_M) == 0)
				more_and_more(philo, philo->table);
		}
	}
	return (NULL);
}
