/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_bye.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 07:40:47 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/12 12:03:16 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_cleanup(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->dead_m);
	pthread_mutex_destroy(&table->print_m);
	while (i < table->philos_n)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

void	clean_bye(t_table *table)
{
	mutex_cleanup(table);
	free(table->philo);
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

void	err_clean_bye(t_table *table, char *str, int i)
{
	char	*err;

	if (i != 0)
	{
		while (i >= 0)
		{
			pthread_join(table->philo[i].th, NULL);
			i--;
		}
	}
	mutex_cleanup(table);
	if (table->philo != NULL)
		free(table->philo);
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
