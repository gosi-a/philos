/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 13:32:01 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/19 09:05:35 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	ft_sleep(philo, philo->data->tt_eat);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
	if (philo->data->meals != -1 && bool_check(philo, PHILO_DEAD_M) == 0)
	{
		philo->meals_eaten += 1;
		if (philo->meals_eaten == philo->data->meals)
		{
			pthread_mutex_lock(&philo->full_m);
			philo->full = true;
			pthread_mutex_unlock(&philo->full_m);
		}
	}
}

static int	go(t_philo *philo)
{
	eat(philo);
	print_status(philo, "is sleeping\n");
	if (ft_sleep(philo, philo->data->tt_sleep) == -1)
		return (-1);
	print_status(philo, "is thinking\n");
	if (philo->data->philos_n % 2 != 0)
		ft_sleep(philo, philo->data->tt_think);
	return (0);
}

static void	one_and_only(t_philo *philo)
{
	philo->time_last_meal = philo->data->started;
	pthread_mutex_lock(philo->right_f);
	print_status(philo, "has taken a fork\n");
	ft_sleep(philo, philo->data->tt_die);
	pthread_mutex_unlock(philo->right_f);
}

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
			if (philo->meals_eaten == philo->data->meals)
				break ;
			if (go(philo) == -1)
				break ;
		}
	}
	return (NULL);
}
