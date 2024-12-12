/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 13:32:01 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/12 15:12:47 by mstencel      ########   odam.nl         */
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

static void	more_and_more(t_philo *philo, t_table *table)
{
	if (philo->id % 2 != 0)
	{
		ft_sleep(table, 50, philo->id);
		if (dead_check(table) == 1)
			return ;
	}
	pthread_mutex_lock(philo->right_f);
	print_state(table, get_time_stamp(table), philo->id, FORK);
	pthread_mutex_lock(philo->left_f);
	print_state(table, get_time_stamp(table), philo->id, FORK);
	philo->time_last_meal = get_time(table);
	print_state(table, get_time_stamp(table), philo->id, EAT);
	if (table->meals != -1)
		philo->meals_eaten += 1;
	ft_sleep(table, table->tt_eat, philo->id);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
	print_state(table, get_time_stamp(table), philo->id, SLEEP);
	ft_sleep(table, get_time_stamp(table), philo->id);
	print_state(table, get_time_stamp(table), philo->id, THINK);
}

void	*go(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	philo->time_last_meal = get_time(table);
	if (table->philos_n == 1)
		one_and_only(philo);
	else
	{
		thread_synch(table);
		while (1)
		{
			more_and_more(philo, table);
			if (dead_check(table) == 1)
				break ;
		}
	}
	return (NULL);
}

void	make_philos(t_table *table)
{
	int	i;
	int	chck;

	i = 0;
	table->started = get_time(table);
	pthread_mutex_lock(&table->start_m);
	while (i < table->philos_n)
	{
		chck = pthread_create(&table->philo[i].th, NULL, &go, \
			(void *)&table->philo[i]);
		if (chck != 0)
			err_clean_bye(table, "pthread_create() failure: philos\n", i);
		i++;
	}
	pthread_mutex_unlock(&table->start_m);
	while (1)
	{
		//for each philo it:
		//should check the time when it has eaten
		//the amount of meals if applicable
		if (dead_check(table) == 1)
			return ;
		usleep(100);
		//will have to make sure other threads will stop
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
