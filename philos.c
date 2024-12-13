/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 13:32:01 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/13 14:36:40 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_and_only(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	print_state(philo->data, get_time_stamp(philo->data), philo->id, FORK);
	ft_sleep(philo->data, philo->data->tt_die, philo->id);
	print_state(philo->data, get_time_stamp(philo->data), philo->id, DIE);
	pthread_mutex_unlock(philo->right_f);
}

static int	forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_f);
		print_state(philo->data, get_time_stamp(philo->data), philo->id, FORK);
		if (philo_mutex_check(philo->data, philo, DEAD_M) == 1)
		{
			pthread_mutex_unlock(philo->left_f);
			return (1);
		}
		pthread_mutex_lock(philo->right_f);
		print_state(philo->data, get_time_stamp(philo->data), philo->id, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_f);
		print_state(philo->data, get_time_stamp(philo->data), philo->id, FORK);
		if (philo_mutex_check(philo->data, philo, DEAD_M) == 1)
		{
			pthread_mutex_unlock(philo->right_f);
			return (1);
		}
		pthread_mutex_lock(philo->left_f);
		print_state(philo->data, get_time_stamp(philo->data), philo->id, FORK);
	}
	return (0);
}

static void	eat(t_philo *philo)
{
	forks(philo);
	change_m_value(philo->data, philo, TIME_LAST_MEAL_M);
	print_state(philo->data, get_time_stamp(philo->data), philo->id, EAT);
	if (philo->data->meals != -1)
	{
		philo->meals_eaten += 1;
		if (philo->meals_eaten == philo->data->meals)
			change_m_value(philo->data, philo, FULL_M);
	}
	ft_sleep(philo->data, philo->data->tt_eat, philo->id);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

static void	more_and_more(t_philo *philo)
{
	long	think_time;

	if (philo_mutex_check(philo->data, philo, DEAD_M) == 0)
		eat(philo);
	print_state(philo->data, get_time_stamp(philo->data), philo->id, SLEEP);
	ft_sleep(philo->data, philo->data->tt_sleep, philo->id);
	print_state(philo->data, get_time_stamp(philo->data), philo->id, THINK);
	if (philo->data->philos_n % 2 != 0)
	{
		think_time = philo->data->tt_eat * 2 - philo->data->tt_sleep;
		if (think_time > 0)
			ft_sleep(philo->data, think_time, philo->id);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	thread_synch(philo->data);
	change_m_value(philo->data, philo, TIME_LAST_MEAL_M);
	if (philo->data->philos_n == 1)
		one_and_only(philo);
	else
	{
		if (philo->id % 2 == 0)
		{
			print_state(philo->data, get_time_stamp(philo->data), \
				philo->id, THINK);
			ft_sleep(philo->data, philo->data->tt_eat / 2, philo->id);
			if (philo_mutex_check(philo->data, philo, DEAD_M) == 1)
				return (NULL);
		}
		while (philo_mutex_check(philo->data, philo, DEAD_M) == 0)
		{
			if (philo_mutex_check(philo->data, philo, FULL_M) == 0)
				more_and_more(philo);
		}
	}
	return (NULL);
}
