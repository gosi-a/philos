/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 13:23:50 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/14 07:17:41 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	change_m_value(t_data *data, t_philo *philo, int flag)
{
	if (flag == DEAD_M)
	{
		pthread_mutex_lock(&data->dead_m);
		data->dead = true;
		pthread_mutex_unlock(&data->dead_m);
	}
	else if (flag == FULL_M)
	{
		pthread_mutex_lock(&philo->full_m);
		philo->full = true;
		pthread_mutex_unlock(&philo->full_m);
	}
	else if (flag == TIME_LAST_MEAL_M)
	{
		pthread_mutex_lock(&philo->time_last_meal_m);
		philo->time_last_meal = get_time(data);
		pthread_mutex_unlock(&philo->time_last_meal_m);
	}
	else if (flag == ALL_FULL_M)
	{
		pthread_mutex_lock(&data->all_full_m);
		data->all_full = true;
		pthread_mutex_unlock(&data->all_full_m);
	}
}

// static void	up_the_meal(t_philo *philo)
// {
// 	philo->meals_eaten += 1;
// 	if (philo->meals_eaten == philo->data->meals)
// 		change_m_value(philo->data, philo, FULL_M);
// }

/// @brief locks the mutex & prints the current philo's state
/// @param data data
/// @param time_stamp from get_time_stamp() 
/// @param id philo's id
/// @param flag FORK EAT SLEEP THINK or DIE (with DIE it sets dead to true)
void	print_state(t_data *data, long time_stamp, int id, int flag)
{
	if (flag == DIE)
	{
		pthread_mutex_lock(&data->print_m);
		if (philo_mutex_check(data, &data->philo[id], DEAD_M) == 0)
			printf(GREEN"%zu"R"\t%d "RED"died\n"R, time_stamp, id);
		change_m_value(data, data->philo, DEAD_M);
		pthread_mutex_unlock(&data->print_m);
	}
	pthread_mutex_lock(&data->print_m);
	if (philo_mutex_check(data, &data->philo[id], DEAD_M) == 0)
	{
		if (flag == FORK)
			printf(GREEN"%zu"R"\t%d has taken a fork\n", time_stamp, id);
		else if (flag == SLEEP)
			printf(GREEN"%zu"R"\t%d is sleeping\n", time_stamp, id);
		else if (flag == THINK)
			printf(GREEN"%zu"R"\t%d is thinking\n", time_stamp, id);
		else if (flag == EAT)
			printf(GREEN"%zu"R"\t%d is eating\n", time_stamp, id);
	}
	pthread_mutex_unlock(&data->print_m);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*new_str;
	int		i;
	int		j;

	if (!str1)
		str1 = "";
	if (!str2)
		str2 = "";
	new_str = malloc(sizeof(char) * ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str1[i])
	{
		new_str[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
	{
		new_str[i + j] = str2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (str[len])
	{
		while (str[len])
			len++;
	}
	return (len);
}
