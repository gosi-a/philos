/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 08:34:27 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/12 08:34:50 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		err_clean_bye(table, "gettimeofday() failure\n", table->philos_n - 1);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (time);	
}


void	ft_sleep(t_table *table, long time, int	philo_id)
{
	long	now;
	long	t_of_death;

	now = get_time(table);
	while (get_time(table) - now < time)
	{
		if (get_time(table) - table->philo->time_last_meal >= table->tt_die)
		{
			t_of_death = get_time_stamp(table);
			print_state(table, t_of_death, philo_id, DIE);
			//it should join the threads, clean the memory & exit
		}
		if (table->dead == true)
			//it should join the threads, clean the memory & exit
		usleep(100);
	}
}
