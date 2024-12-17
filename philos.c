/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 13:32:01 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/17 10:56:06 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_and_only(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	print_status(philo, "has taken a fork\n");
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
		print_status(philo, "has taken a fork\n");
		if (bool_check(philo, PHILO_DEAD_M) == 1)
		{
			pthread_mutex_unlock(philo->left_f);
			return (1);
		}
		pthread_mutex_lock(philo->right_f);
		print_status(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->right_f);
		print_status(philo, "has taken a fork\n");
		if (bool_check(philo, PHILO_DEAD_M) == 1)
		{
			pthread_mutex_unlock(philo->right_f);
			return (1);
		}
		pthread_mutex_lock(philo->left_f);
		print_status(philo, "has taken a fork\n");
	}
	return (0);
}

static void	eat(t_philo *philo)
{
	if (forks(philo) == 1)
		return ;
	print_status(philo, "is eating\n");
	pthread_mutex_lock(&philo->time_last_meal_m);
	philo->time_last_meal = get_time(philo->data);
	pthread_mutex_unlock(&philo->time_last_meal_m);
	philo->meals_eaten += 1;
	ft_sleep(philo, philo->data->tt_eat);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
	if (philo->data->meals != -1 && bool_check(philo, PHILO_DEAD_M) == 0)
	{
		if (philo->meals_eaten == philo->data->meals)
		{
			pthread_mutex_lock(&philo->full_m);
			philo->full = true;
			pthread_mutex_unlock(&philo->full_m);
		}
	}
}

/// @brief sync of the philos, sets up the start time, if 1 philo only, 
//		another function, for more, even philos will sleep half of the tt_eat,
//		they will eat, sleep & think 
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
		while (bool_check(philo, PHILO_DEAD_M) == 0)
		{
			eat(philo);
			print_status(philo, "is sleeping\n");
			if (ft_sleep(philo, philo->data->tt_sleep) == -1)
				break ;
			print_status(philo, "is thinking\n");
			ft_sleep(philo, philo->data->tt_think);
		}
	}
	return (NULL);
}
