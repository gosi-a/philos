/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_bye.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 07:40:47 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/14 12:11:10 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_cleanup(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->end_m);
	pthread_mutex_destroy(&data->print_m);
	pthread_mutex_destroy(&data->start_m);
	while (i < data->philos_n)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].full_m);
		pthread_mutex_destroy(&data->philo[i].time_last_meal_m);
		i++;
	}
	free(data->forks);
}

void	clean_bye(t_data *data)
{
	mutex_cleanup(data);
	free(data->philo);
}

void	err_bye(char *str)
{
	char	*err;

	err = ft_strjoin("\033[1;31mError: \033[0m", str);
	if (!err)
	{
		write(2, "\033[1;31mError:\033[0m err_bye: ft_strjoin()\n", 31);
		exit (1);
	}
	write(2, err, ft_strlen(err));
	free(err);
	exit (1);
}

void	err_clean_bye(t_data *data, char *str, int i)
{
	char	*err;

	if (i != 0)
	{
		while (i >= 0)
		{
			pthread_join(data->philo[i].th, NULL);
			i--;
		}
	}
	mutex_cleanup(data);
	if (data->philo != NULL)
		free(data->philo);
	err = ft_strjoin("\033[1;31mError: \033[0m", str);
	if (!err)
	{
		write(2, "\033[1;31mError:\033[0m err_clean_bye: ft_strjoin()\n", 31);
		exit (1);
	}
	write(2, err, ft_strlen(err));
	free(err);
	exit (1);
}
