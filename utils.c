/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 13:23:50 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/10 13:43:04 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(long time, int id, int flag)
{
	if (flag == FORK)
		printf("%zu %d has taken a fork\n", time, id);
	else if (flag == EAT)
		printf("%zu %d is eating\n", time, id);
	else if (flag == SLEEP)
		printf("%zu %d is sleeping\n", time, id);
	else if (flag == THINK)
		printf("%zu %d is thinking\n", time, id);
	else if (flag == DIE)
		printf("%zu %d died\n", time, id);
}

long	get_time_stamp(t_table * table)
{
	long	now;
	long	time_stamp;

	now = get_time(table);
	time_stamp = now - table->started;
	return (time_stamp);
}

long	get_time(t_table *table)
{
	struct timeval	now;
	long			time;
	
	if (gettimeofday(&now, NULL) != 0)
		err_clean_bye(table, "gettimeofday() failure");
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (time);	
}


			/*to delete*/
void	print_table(t_table *table)
{
	printf("philos: %d\t", table->philos_num);
	printf("die: %d\t", table->tt_die);
	printf("eat: %d\t", table->tt_eat);
	printf("sleep: %d\t",table->tt_sleep);
	printf("meals: %d\n",table->meals);
}
