/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 13:23:50 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/14 12:12:17 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief sets the value to true or gets the time of the last meal
/// @param philo 
/// @param flag END_M FULL_M TIME_LAST_MEAL_M PHILO_DEAD_M
void	change_m_value(t_philo *philo, int flag)
{
	if (flag == END_M)
	{
		pthread_mutex_lock(&philo->data->end_m);
		philo->data->end = true;
		pthread_mutex_unlock(&philo->data->end_m);
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
		philo->time_last_meal = get_time(philo->data);
		pthread_mutex_unlock(&philo->time_last_meal_m);
	}
	else if (flag == PHILO_DEAD_M)
	{
		pthread_mutex_lock(&philo->philo_dead_m);
		philo->philo_dead = true;
		pthread_mutex_unlock(&philo->philo_dead_m);
	}
}

/// @brief locks the mutex & prints the current philo's state, 
//		if dead (flag DIE), updates the philo's death state
/// @param data data for the mutexes (&norminette o_0 )
/// @param time_stamp from get_time_stamp() 
/// @param id philo's id for printing
/// @param flag FORK EAT SLEEP THINK or DIE (with DIE it sets dead to true)
void	print_state(t_philo *philo, long time_stamp, int flag)
{
	if (flag == DIE)
	{
		pthread_mutex_lock(&philo->data->print_m);
		if (philo_mutex_check(philo, PHILO_DEAD_M) == 0
			&& philo_mutex_check(philo, END_M) == 0)
			printf(GRN"%zu"R"\t%d "RED"died\n"R, time_stamp, philo->id);
		change_m_value(philo, PHILO_DEAD_M);
		pthread_mutex_unlock(&philo->data->print_m);
	}
	pthread_mutex_lock(&philo->data->print_m);
	if (philo_mutex_check(philo, END_M) == 0
		&& philo_mutex_check(philo, PHILO_DEAD_M) == 0)
	{
		if (flag == FORK)
			printf(GRN"%zu"R"\t%d has taken a fork\n", time_stamp, philo->id);
		else if (flag == SLEEP)
			printf(GRN"%zu"R"\t%d is sleeping\n", time_stamp, philo->id);
		else if (flag == THINK)
			printf(GRN"%zu"R"\t%d is thinking\n", time_stamp, philo->id);
		else if (flag == EAT)
			printf(GRN"%zu"R"\t%d is eating\n", time_stamp, philo->id);
	}
	pthread_mutex_unlock(&philo->data->print_m);
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
