/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 13:32:01 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/14 12:10:57 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void	one_and_only(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	print_state(philo, get_time_stamp(philo->data), FORK);
	ft_sleep(philo, philo->data->tt_die);
	pthread_mutex_unlock(philo->right_f);
}

/// @brief even philos will start eating with their left fork & odd with their
///		right fork, also checks if philo is dead, it won't be able to eat
/// @param philo 
static int	forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_f);
		print_state(philo, get_time_stamp(philo->data), FORK);
		if (philo_mutex_check(philo, END_M) == 1)
		{
			pthread_mutex_unlock(philo->left_f);
			return (1);
		}
		pthread_mutex_lock(philo->right_f);
		print_state(philo, get_time_stamp(philo->data), FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_f);
		print_state(philo, get_time_stamp(philo->data), FORK);
		if (philo_mutex_check(philo, END_M) == 1)
		{
			pthread_mutex_unlock(philo->right_f);
			return (1);
		}
		pthread_mutex_lock(philo->left_f);
		print_state(philo, get_time_stamp(philo->data), FORK);
	}
	return (0);
}

static void	eat(t_philo *philo)
{
	if (philo_mutex_check(philo, END_M) == 1)
		return ;
	if (forks(philo) == 1)
		return ;
	change_m_value(philo, TIME_LAST_MEAL_M);
	print_state(philo, get_time_stamp(philo->data), EAT);
	philo->meals_eaten += 1;
	ft_sleep(philo, philo->data->tt_eat);
	if (philo->meals_eaten == philo->data->meals)
		change_m_value(philo, FULL_M);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

static void	more_and_more(t_philo *philo)
{
	long	think_time;

	while (philo_mutex_check(philo, END_M) == 0)
	{
		eat(philo);
		print_state(philo, get_time_stamp(philo->data), SLEEP);
		ft_sleep(philo, philo->data->tt_sleep);
		print_state(philo, get_time_stamp(philo->data), THINK);
		if (philo->data->philos_n % 2 != 0)
		{
			think_time = philo->data->tt_eat * 2 - philo->data->tt_sleep;
			if (think_time > 0)
				ft_sleep(philo, think_time);
		}
	}
}

/// @brief sync of the philos, sets up the start time, if 1 philo only, 
//		another function, for more, even philos will sleep half of the tt_eat,
//		they go to the eat, sleep & think part 
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	thread_synch(philo);
	change_m_value(philo, TIME_LAST_MEAL_M);
	if (philo->data->philos_n == 1)
		one_and_only(philo);
	else
	{
		if (philo->id % 2 == 0)
		{
			ft_sleep(philo, philo->data->tt_eat / 2);
			if (philo_mutex_check(philo, END_M) == 1)
				return (NULL);
		}
		more_and_more(philo);
	}
	return (NULL);
}
