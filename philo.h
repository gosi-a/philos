/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/07 06:51:04 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/13 12:04:44 by mstencel      ########   odam.nl         */
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

/*for printing the status*/
# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

/*mutex*/
# define FORK_M 0
# define FULL_M 1
# define TIME_LAST_MEAL_M 2
# define DEAD_M 3

# define R "\033[0m"
# define RED "\033[31;1m"
# define GREEN "\033[38;5;82m"

struct	s_table;

typedef struct	s_philo
{
	int				id;
	int				meals_eaten;
	long			time_last_meal;
	bool			full;
	pthread_t		th;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	full_m;
	pthread_mutex_t	time_last_meal_m;
	struct s_table	*table;
}	t_philo;

typedef struct	s_table
{
	bool			dead;
	int				meals;
	int				philos_n;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	long			started;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_m;
	pthread_mutex_t	print_m;
	pthread_mutex_t	start_m;
}	t_table;

void	init(t_table *table, char **argv, int argc);
void	parse(t_table *table, char **argv, int argc);
void	*routine(void *arg);

			/*error & cleaning*/
void	err_bye(char *str);
void	err_clean_bye(t_table *table, char *str, int i);
void	mutex_cleanup(t_table *table);
void	clean_bye(t_table *table);

			/*time*/
long	get_time_stamp(t_table *table);
long	get_time(t_table *table);
void	ft_sleep(t_table *table, long sleep_time, int id);
void	thread_synch(t_table *table);

			/*checks*/
int		total_check(t_table *table);
int		philo_mutex_check(t_table *table, t_philo *philo, int flag);
long	philos_mutex_long_check(t_philo *philo);
void	change_m_value(t_table *table, t_philo *philo, int flag);

			/*utils*/
int		ft_strlen(char *str);
char	*ft_strjoin(char *str1, char *str2);
void	print_state(t_table *table, long time_stamp, int id, int flag);

#endif