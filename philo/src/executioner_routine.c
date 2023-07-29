/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:40:15 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/29 18:11:24 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
checks if a philo has exceeded their time of starvation.
If greater, it marks the philosopher as dead,
prints a death message with the timestamp and philo's name.
*/
int	check_last_meal(t_philo *philo)
{
	if (get_time() - philo->data->starting_time >= philo->time_of_starvation)
	{
		philo->data->first_death = true;
		usleep(10);
		printf(RED BOLD"%ld %d died" RESET "\n", 
			get_time() - philo->data->starting_time, philo->name);
		return (DEATH);
	}
	else
		return (ALIVE);
}

/*
Checking all philos if one of them is dead.
*/
int	bringing_out_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (check_last_meal(&data->philo[i]) == DEATH)
			return (DEATH);
		i++;
	}
	return (ALIVE);
}

/*
Checking if philo has eaten number of meal from last argument.
*/
bool	is_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->food_mutex);
	if (philo->data->number_of_meals == philo->meals_eaten)
	{
		pthread_mutex_unlock(&philo->data->food_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->food_mutex);
	return (false);
}

/*
Checking until all philos are full.
*/
bool	everybody_full(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (is_full(&data->philo[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

/*
The executioner thread continuously checks the status of all philos
to detect any deaths due to starvation and if all philosophers
have finished their meals. If any philosopher is dead,
the executioner returns immediately. If all philosophers are full,
it also returns.
*/
void	*executioner_rtn(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->cemetary_mutex);
		if (bringing_out_dead(data) == DEATH) 
		{
			usleep(100);
			pthread_mutex_unlock(&data->cemetary_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->cemetary_mutex);
		if (everybody_full(data))
			return (NULL);
		usleep(200);
	}
	return (NULL);
}
