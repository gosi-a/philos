/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/07 06:51:04 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/17 10:08:03 by mstencel      ########   odam.nl         */
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

/*mutex*/
# define FORK_M 0
# define FULL_M 1
# define TIME_LAST_MEAL_M 2
# define PHILO_DEAD_M 3

# define R "\033[0m"
# define RED "\033[31;1m"
// # define GRN "\033[38;5;82m"

struct	s_data;

/// @brief includes philo's actual thread & info:
//	id, how many meals it had, the time of the last meal, bool if it's full
//	mutexes: pointers to assigned right_f (it's own) & left_f (borrowed) +
//	for the bool & time of the last meal
//	pointer to data for info
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			time_last_meal;
	bool			full;
	bool			philo_dead;
	pthread_t		th;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	full_m;
	pthread_mutex_t	philo_dead_m;
	pthread_mutex_t	time_last_meal_m;
	struct s_data	*data;
}	t_philo;

/// @brief contains all the main info:
//	n of philo, all the times, max n meals, start_time & *philo +
//	flag: end +
//	mutexes: malloc'ed forks array (1 per philo), print, 
//		start for synch philos, for the flags
typedef struct s_data
{
	int				meals;
	int				philos_n;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				tt_think;
	long			started;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_m;
	pthread_mutex_t	start_m;
}	t_data;

int	init(t_data *data, char **argv, int argc);
int	parse(t_data *data, char **argv, int argc);
void	*routine(void *arg);

			/*error & cleaning*/
void	err_bye(char *str);
int		err_clean_bye(t_data *data, char *str, int i);
void	mutex_cleanup(t_data *data);
void	clean_bye(t_data *data);

			/*time*/
long	get_time_stamp(t_data *data);
long	get_time(t_data *data);
int		ft_sleep(t_philo *philo, long sleep_time);

			/*monitoring*/
void	monitoring(t_data *data);

			/*printing*/
void	print_status(t_philo *philo, char *str);
void	print_fork(t_philo *philo);
void	print_eat(t_philo *philo);
void	print_sleep(t_philo *philo);
void	print_think(t_philo *philo);

			/*utils*/
int		bool_check(t_philo *philo, int flag);
int		ft_strlen(char *str);
char	*ft_strjoin(char *str1, char *str2);

#endif