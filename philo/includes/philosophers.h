/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:25:59 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/28 20:03:41 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>

# define DEATH 0
# define ALIVE 1
# define BOLD    "\033[1m"
# define RED	"\e[31m"
# define WHITE   "\033[97m"
# define BRIGHT_YELLOW  "\033[93m"
# define YELLOW  "\033[33m"
# define CYAN	"\e[36m"
# define RESET   "\033[0m"
# define STR_USAGE	"Usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_meals_each_philosopher_must_eat]"
# define STR_VALID_INPUT "Input value has to \
be a positive integer between 0 and 2147483647.\n"
# define STR_PHILO_MAX  "Philosophers has to be \
in range of 1 and 250.\n"

typedef struct s_data
{
	unsigned int		philo_count;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	time_t				number_of_meals;
	time_t				starting_time;
	bool				first_death;
	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		time_mutex;
	pthread_mutex_t		food_mutex;
	pthread_mutex_t		cemetary_mutex;	
	struct s_philo		*philo;
	pthread_t			t_executioner_id;
}	t_data;

typedef struct s_philo
{
	pthread_t		t_id;
	unsigned int	name;
	time_t			time_of_last_meal;
	time_t			time_of_starvation;
	unsigned int	meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

/*
main.c
Initialization of the data structures, mutexes and simulation itself.
*/
int		init_philos(t_data *data);
int		init_mutex(t_data *data);
void	init(t_data *data, char **argv);
void	simulacrum(t_data *data);

/*
philo_routine.c & philo_routine_eating.c
Thread routine for each philosopher.
*/
void	*philo_rtn(void *philosopher);
void	*lone_philo_rtn(void *philosopher);
void	philo_is_thinking(t_philo *philo, bool start);
void	philo_is_sleeping(t_philo *philo);
bool	is_dead(t_philo *philo);

void	philo_is_eating(t_philo *philo);
void	returning_forks(t_philo *philo);
void	devouring(t_philo *philo);
int		taking_forks(t_philo *philo);

/*
executioner.c
Thread routine which checks if anybody is starving and kills hungry philosophers.
*/
void	*executioner_rtn(void *arg);
int		bringing_out_dead(t_data *data);
int		check_last_meal(t_philo *philo);
bool	is_full(t_philo *philo);
bool	everybody_full(t_data *data);

/*
argument_check.c
*/
bool	args_check(int argc, char **argv);

/*
utils.c
*/
void	mutex_cide(t_data *data);
int		ft_atoi(char *str);
time_t	get_time(void);
void	print_message(char *colour, char *str, t_philo *philo);
void	ft_sleep(int time_to, t_philo *philosophers);

#endif
