/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 08:05:48 by mstencel      #+#    #+#                 */
/*   Updated: 2025/01/16 11:55:50 by mstencel      ########   odam.nl         */
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

	if (!str || str[0] == '\0')
		return (err_bye("invalid input: use numbers as an input\n"));
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (err_bye("invalid input: use positive values\n"));
	j = i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (err_bye("invalid input: use numbers only\n"));
		i++;
	}
	value = ft_atol(str, j);
	if (value > INT_MAX)
		return (err_bye("invalid input: too big number, use integers\n"));
	return ((int)value);
}

static int	get_args(t_data *data, char **argv, int argc)
{
	data->philos_n = get_value(argv[1]);
	if (data->philos_n == -1)
		return (-1);
	if (data->philos_n > 200 || data->philos_n <= 0)
		return (err_bye("invalid input: philosphers range: 1-200\n"));
	data->tt_die = get_value(argv[2]);
	if (data->tt_die == -1)
		return (-1);
	data->tt_eat = get_value(argv[3]);
	if (data->tt_eat == -1)
		return (-1);
	data->tt_sleep = get_value(argv[4]);
	if (data->tt_sleep == -1)
		return (-1);
	if (argc == 6)
	{
		data->meals = get_value(argv[5]);
		if (data->meals == 0)
			return (err_bye("invalid input: if used, minimum meals: 1\n"));
	}
	else
		data->meals = -1;
	return (0);
}

int	parse(t_data *data, char **argv, int argc)
{
	int	think;

	if (get_args(data, argv, argc) == -1)
		return (-1);
	think = data->tt_eat * 2 - data->tt_sleep;
	if (think > 0)
		data->tt_think = think;
	else
		data->tt_think = 0;
	return (0);
}
