/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 13:23:50 by mstencel      #+#    #+#                 */
/*   Updated: 2025/01/16 11:56:39 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->philo_dead_m);
	if (philo->philo_dead == false)
	{
		pthread_mutex_lock(&philo->data->print_m);
		printf("%zu %d %s", get_time_stamp(philo->data), philo->id, str);
		pthread_mutex_unlock(&philo->data->print_m);
	}
	pthread_mutex_unlock(&philo->philo_dead_m);
}

/// @brief checks safely if philo's bool is set to true
/// @return 1 if dead is true 0 if dead is false
int	bool_check(t_philo *philo, int flag)
{
	if (flag == FULL_M)
	{
		pthread_mutex_lock(&philo->full_m);
		if (philo->full == true)
		{
			pthread_mutex_unlock(&philo->full_m);
			return (1);
		}
		pthread_mutex_unlock(&philo->full_m);
	}
	else if (flag == PHILO_DEAD_M)
	{
		pthread_mutex_lock(&philo->philo_dead_m);
		if (philo->philo_dead == true)
		{
			pthread_mutex_unlock(&philo->philo_dead_m);
			return (1);
		}
		pthread_mutex_unlock(&philo->philo_dead_m);
	}
	return (0);
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
