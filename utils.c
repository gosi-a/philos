/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 13:23:50 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/12 08:46:31 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strjoin(char *str1, char *str2)
{
	char 	*new_str;
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

void	print_state(t_table *table, long time, int id, int flag)
{
	pthread_mutex_lock(&table->print_m);
	if (flag == FORK && table->dead == false)
		printf("%zu %d has taken a fork\n", time, id);
	else if (flag == EAT && table->dead == false)
		printf("%zu %d is eating\n", time, id);
	else if (flag == SLEEP && table->dead == false)
		printf("%zu %d is sleeping\n", time, id);
	else if (flag == THINK && table->dead == false)
		printf("%zu %d is thinking\n", time, id);
	else if (flag == DIE && table->dead == false)
	{
		table->dead = true;
		printf("%zu %d died\n", time, id);
	}
	pthread_mutex_unlock(&table->print_m);
}



			/*to delete*/
void	print_table(t_table *table)
{
	printf("philos: %d\t", table->philos_n);
	printf("die: %d\t", table->tt_die);
	printf("eat: %d\t", table->tt_eat);
	printf("sleep: %d\t",table->tt_sleep);
	printf("meals: %d\n",table->meals);
}
