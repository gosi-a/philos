/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/07 06:51:04 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/12 09:14:55 by mstencel      ########   odam.nl         */
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
	pthread_t		th;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
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
	pthread_mutex_t	print_m;
}	t_table;

void	init(t_table *table, char **argv, int argc);
void	parse(t_table *table, char **argv, int argc);

			/*error & cleaning*/
void	err_bye(char *str);
void	err_clean_bye(t_table *table, char *str, int i);
void	mutex_cleanup(t_table *table);
void	clean_bye(t_table *table);

			/*time*/
long	get_time_stamp(t_table *table);
long	get_time(t_table *table);
void	ft_sleep(t_table *table, long time, int philo_id);

			/*utils*/
int		ft_strlen(char *str);
char	*ft_strjoin(char *str1, char *str2);
void	print_state(t_table *table, long time, int id, int flag);

			/*to delete*/
void	print_table(t_table *table);

#endif