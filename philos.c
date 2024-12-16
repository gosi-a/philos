/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 13:32:01 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/16 13:35:13 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	one_and_only(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	print_state(philo, FORK);
	ft_sleep(philo, philo->data->tt_die);
	pthread_mutex_unlock(philo->right_f);
	return (0);
}

/// @brief even philos will start eating with their left fork & odd with their
///		right fork, also checks if philo is dead, it won't be able to eat
/// @param philo 
static int	forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_f);
		print_state(philo, FORK);
		if (is_alive(philo) == 1)
		{
			pthread_mutex_unlock(philo->left_f);
			return (1);
		}
		pthread_mutex_lock(philo->right_f);
		print_state(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_f);
		print_state(philo, FORK);
		if (is_alive(philo) == 1)
		{
			pthread_mutex_unlock(philo->right_f);
			return (1);
		}
		pthread_mutex_lock(philo->left_f);
		print_state(philo, FORK);
	}
	return (0);
}

static int	eat(t_philo *philo)
{
	// if (is_alive(philo) == 1)
	// 	return (-1);
	printf("%d is going to eat\n", philo->id);
	if (forks(philo) == 1)
		return (-1);
	if (print_state(philo, EAT) == -1)
		return (-1);
	change_m_value(philo, TIME_LAST_MEAL_M);
	philo->meals_eaten += 1;
	if (ft_sleep(philo, philo->data->tt_eat) == -1)
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		return (-1);
	}
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
	if (is_alive(philo) == 1)
		return (-1);
	if (philo->data->meals != -1)
	{
		if (philo->meals_eaten == philo->data->meals
			&& is_alive(philo) == 0)
			change_m_value(philo, FULL_M);
	}
	return (0);
}

static int	more_and_more(t_philo *philo)
{
	// long	think_time;

	while (is_alive(philo) == 0)
	{
		if (eat(philo) == -1)
			return (-1);
		if (is_alive(philo) == 1)
			return (-1);
		print_state(philo, SLEEP);
		if (ft_sleep(philo, philo->data->tt_sleep) == -1)
			return (-1);
		if (is_alive(philo) == 1)
			return (-1);
		print_state(philo, THINK);
		// if (philo->data->philos_n % 2 != 0)
		// {
		// 	think_time = (philo->data->tt_eat * 2) - philo->data->tt_sleep;
		// 	if (think_time > 0)
		// 	{
		// 		if (ft_sleep(philo, think_time) == -1)
		// 			return (-1);
		// 	}
		// }
	}
	return (0);
}

/// @brief sync of the philos, sets up the start time, if 1 philo only, 
//		another function, for more, even philos will sleep half of the tt_eat,
//		they go to the eat, sleep & think part 
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->start_m);
	pthread_mutex_unlock(&philo->data->start_m);
	if (philo->data->philos_n == 1)
		one_and_only(philo);
	else
	{
		if (philo->id % 2 == 0)
		{
			if (ft_sleep(philo, philo->data->tt_eat / 2) == -1)
				return (NULL);
		}
		if (more_and_more(philo) == -1)
			return (NULL);
	}
	return (NULL);
}
