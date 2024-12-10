/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/07 06:51:04 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/10 13:31:29 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

struct	s_table;

typedef struct	s_philo
{
	int				id;
	int				meals_eaten;
	long			time_last_meal;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	struct s_table	*table;
}	t_philo;

typedef	struct s_table
{
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	long			started;
	pthread_mutex_t	began_m;
	bool			dead;
	pthread_mutex_t	dead_m;
	int				meals;
	pthread_mutex_t	meal_m;
	pthread_mutex_t	print_m;
	int				philos_num;
	t_philo			*philo;
	pthread_mutex_t	*forks;
}	t_table;

void	init(t_table *table, char **argv, int argc);
void	parse(t_table *table, char **argv,int argc);

			/*error & cleaning*/
void	err_bye(char *str);
void	err_clean_bye(t_table *table, char *str);
void	mutex_cleanup(t_table *table);
void	clean_bye(t_table *table);

			/*utils*/
void	print_state(long time, int id, int flag);
long	get_time_stamp(t_table * table);
long	get_time(t_table *table);

			/*to delete*/
void	print_table(t_table *table);

#endif