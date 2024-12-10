/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_bye.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 07:40:47 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/10 12:08:00 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	typedef struct	s_philo
{
	int				id;
	int				meals_eaten;
	long			time_last_meal;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	t_table			*table;
}	t_philo;

typedef	struct s_table
{
	bool			dead;
	int				meals;
	int				philos_num;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	long			started;
	pthread_t		*forks;
	pthread_t		*philo;
	pthread_mutex_t	began_m;
	pthread_mutex_t	dead_m;
	pthread_mutex_t	meal_m;
	pthread_mutex_t	print_m;
}	t_table;
*/

static int	ft_strlen(char *str)
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

void	clean_bye(t_table *table)
{
	mutex_cleanup(table);
	free(table->philo);
}

void	mutex_cleanup(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->began_m);
	pthread_mutex_destroy(&table->dead_m);
	pthread_mutex_destroy(&table->meal_m);
	pthread_mutex_destroy(&table->print_m);
	while (i < table->philos_num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

void	err_bye(char *str)
{
	write(2, "\033[1;31mError: \033[0m", 19);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit (1);
}

void	err_clean_bye(t_table *table, char *str)
{
	mutex_cleanup(table);
	if (table->philo != NULL)
		free(table->philo);
	write(2, "\033[1;31mError: \033[0m", 19);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit (1);
}
