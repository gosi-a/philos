/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_state.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/17 08:22:42 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/17 10:41:13 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->philo_dead_m);
	if (philo->philo_dead == false)
	{
		pthread_mutex_lock(&philo->data->print_m);
		printf("%zu\t%d %s", get_time_stamp(philo->data), philo->id, str);
		pthread_mutex_unlock(&philo->data->print_m);
	}
	pthread_mutex_unlock(&philo->philo_dead_m);
}

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_dead_m);
	if (philo->philo_dead == false)
	{
		pthread_mutex_lock(&philo->data->print_m);
		printf("%zu\t%d has taken a fork\n", \
			get_time_stamp(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print_m);
	}
	pthread_mutex_unlock(&philo->philo_dead_m);
}

void	print_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_dead_m);
	if (philo->philo_dead == false)
	{	
		pthread_mutex_lock(&philo->data->print_m);
		printf("%zu\t%d is eating\n", \
			get_time_stamp(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print_m);
	}
	pthread_mutex_unlock(&philo->philo_dead_m);
}

void	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_dead_m);
	if (philo->philo_dead == false)
	{
		pthread_mutex_lock(&philo->data->print_m);
		printf("%zu\t%d is sleeping\n", \
			get_time_stamp(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print_m);
	}
	pthread_mutex_unlock(&philo->philo_dead_m);
}

void	print_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_dead_m);
	if (philo->philo_dead == false)
	{
		pthread_mutex_lock(&philo->data->print_m);
		printf("%zu\t%d is thinking\n", \
			get_time_stamp(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print_m);
	}
	pthread_mutex_unlock(&philo->philo_dead_m);
}
