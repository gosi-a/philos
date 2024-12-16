/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 08:05:48 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/16 12:55:07 by mstencel      ########   odam.nl         */
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
	int		i;
	int		j;
	long	value;

	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		err_bye("invalid input: use positive values\n");
	j = i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			err_bye("invalid input: use numbers only\n");
		i++;
	}
	value = ft_atol(str, j);
	if (value > INT_MAX)
		err_bye("invalid input: too big number, use integers\n");
	return ((int)value);
}

int	parse(t_data *data, char **argv, int argc)
{
	data->philos_n = get_value(argv[1]);
	if (data->philos_n > 200 || data->philos_n == 0)
	{
		err_bye("invalid input: philosphers range: 1-200\n");
		return (-1);
	}
	data->tt_die = get_value(argv[2]);
	data->tt_eat = get_value(argv[3]);
	data->tt_sleep = get_value(argv[4]);
	if (argc == 6)
		data->meals = get_value(argv[5]);
	else
		data->meals = -1;
	return (0);
}
