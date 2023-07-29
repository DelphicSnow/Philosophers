/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:06:37 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/28 19:42:12 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Allocates the array of structures for every philo
and assigns them alligning forks.
*/
int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philo)
	{
		write(2, "Error: Could not allocate memory.\n", 35);
		exit (1);
	}
	while (i < data->philo_count)
	{
		data->philo[i].name = i + 1;
		data->philo[i].right_fork = &data->fork_mutex[i];
		data->philo[i].left_fork = &data->fork_mutex[(i + 1)
			% data->philo_count];
		data->philo[i].data = data;
		data->philo[i].time_of_starvation = data->time_to_die;
		data->philo[i].time_of_last_meal = 0;
		data->philo[i].meals_eaten = 0;
		i++;
	}
	return (0);
}

/*
Allocates mutexe for every fork
and some supplementary mutexes for other shared resources.
*/
int	init_mutex(t_data *data)
{
	int	i;
	int	mutex_error;

	i = 0;
	data->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_count);
	if (!data->fork_mutex)
	{
		write(2, "Error: Could not allocate memory.\n", 35);
		exit (1);
	}
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->fork_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->time_mutex, NULL);
	pthread_mutex_init(&data->food_mutex, NULL);
	pthread_mutex_init(&data->cemetary_mutex, NULL);
	return (0);
}

void	init(t_data *data, char **argv)
{
	int	i;

	i = 1;
	data->philo_count = ft_atoi(argv[i++]);
	data->time_to_die = ft_atoi(argv[i++]);
	data->time_to_eat = ft_atoi(argv[i++]);
	data->time_to_sleep = ft_atoi(argv[i++]);
	if (argv[i])
		data->number_of_meals = ft_atoi(argv[i]);
	else
		data->number_of_meals = -1;
	data->first_death = false;
	init_mutex(data);
	init_philos(data);
}

void	simulacrum(t_data *data)
{
	unsigned int	i;

	i = 0;
	data->starting_time = get_time();
	if (data->philo_count == 1)
		pthread_create(&data->philo[i].t_id, NULL,
			&lone_philo_rtn, (void *)&data->philo[i]);
	else
	{
		while (i < data->philo_count)
		{
			pthread_create(&data->philo[i].t_id, NULL,
				&philo_rtn, (void *)&data->philo[i]);
			i++;
		}
	}
	pthread_create(&data->t_executioner_id, NULL,
		&executioner_rtn, (void *)data);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philo[i].t_id, NULL);
		i++;
	}
	pthread_join(data->t_executioner_id, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		printf("%s\n", STR_USAGE);
	else if (args_check(argc, argv))
	{
		init(&data, argv);
		simulacrum(&data);
		mutex_cide(&data);
		free(data.philo);
	}
}
