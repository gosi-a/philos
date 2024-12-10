/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 08:05:48 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/10 11:54:23 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static long	ft_atol(char *str, int j)
{
	long	value;

	value = 0;
	while (str[j])
	{
		value = value * 10 + str[j] - '0';
		j++;
	}
	return (value);
}

static int	get_value(char *str)
{
	int	i;
	int	j;
	long	value;
	
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		err_bye("invalid input: use positive values");
	j = i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			err_bye("invalid input: use numbers only");
		i++;
	}
	value = ft_atol(str, j);
	if (value > INT_MAX)
		err_bye("invalid input: too big number, use integers");
	return ((int)value);
}

void	parse(t_table *table, char **argv,int argc)
{
	table->philos_num = get_value(argv[1]);
	if (table->philos_num > 200 || table->philos_num == 0)
		err_bye("invalid input: philosphers range: 1-200");
	table->tt_die = get_value(argv[2]);
	table->tt_eat = get_value(argv[3]);
	table->tt_sleep = get_value(argv[4]);
	if (argc == 6)
		table->meals = get_value(argv[5]);
	else
		table->meals = -1;
	//TODO -> add the written message that the 1 philo died after the
	// if (table->philos_num == 1)
	// 	print_state(need to get the time stamp, 1, DIE);
	print_table(table);		// <--to delete
}
