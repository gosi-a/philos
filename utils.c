/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 13:23:50 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/12 14:58:20 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief makes sure that all threads start together (no barrier allowed)
/// @param table 
void	thread_synch(t_table *table)
{
	pthread_mutex_lock(&table->start_m);
	pthread_mutex_unlock(&table->start_m);
}

/// @brief checks safely if philo bool is set to true
/// @param table 
/// @return 1 if dead is true 0 if dead is false
int	dead_check(t_table *table)
{
	bool	check;
	
	pthread_mutex_lock(&table->dead_m);
	check = table->dead;
	pthread_mutex_unlock(&table->dead_m);
	if (check == false)
		return (0);
	return (1);
}

/// @brief locks the mutex & prints the current philo's state
/// @param table data
/// @param time_stamp from get_time_stamp() 
/// @param id philo's id
/// @param flag FORK EAT SLEEP THINK or DIE (with DIE it sets dead to true)
void	print_state(t_table *table, long time_stamp, int id, int flag)
{
	
	if (flag == FORK && dead_check(table) == 0)
	{
		pthread_mutex_lock(&table->print_m);
		printf(GREEN"%zu"R"\t%d has taken a fork\n", time_stamp, id);
		pthread_mutex_unlock(&table->print_m);
	}
	else if (flag == EAT && dead_check(table) == 0)
	{
		pthread_mutex_lock(&table->print_m);
		printf(GREEN"%zu"R"\t%d is eating\n", time_stamp, id);
		pthread_mutex_unlock(&table->print_m);
	}
	else if (flag == SLEEP && dead_check(table) == 0)
	{
		pthread_mutex_lock(&table->print_m);
		printf(GREEN"%zu"R"\t%d is sleeping\n", time_stamp, id);
		pthread_mutex_unlock(&table->print_m);
	}
	else if (flag == THINK && dead_check(table) == 0)
	{
		pthread_mutex_lock(&table->print_m);
		printf(GREEN"%zu"R"\t%d is thinking\n", time_stamp, id);
		pthread_mutex_unlock(&table->print_m);
	}
	else if (flag == DIE && dead_check(table) == 0)
	{
		pthread_mutex_lock(&table->dead_m);
		table->dead = true;
		pthread_mutex_unlock(&table->dead_m);
		pthread_mutex_lock(&table->print_m);
		printf(GREEN"%zu"R"\t%d "RED"died\n"R, time_stamp, id);
		pthread_mutex_unlock(&table->print_m);
	}
	
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
