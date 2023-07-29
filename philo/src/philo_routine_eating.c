/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_eating.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:47:08 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/28 19:44:43 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
It is responsible for the philo attempting to take forks (mutexes) to eat.
It checks whether the philo's name is even or odd and locks the corresponding
forks accordingly to avoid deadlock.
*/
int	taking_forks(t_philo *philo)
{
	if (philo->name % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (is_dead(philo) == false || is_full(philo) == false)
		print_message(YELLOW, "has taken a fork", philo);
	if (philo->name % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (is_dead(philo) == false || is_full(philo) == false)
			print_message(YELLOW, "has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (is_dead(philo) == false || is_full(philo) == false)
			print_message(YELLOW, "has taken a fork", philo);
	}
	return (0);
}

/*
Prints a message that the philo is eating, updates the time of
the philosopher's last meal and the time until they starve.
*/
void	devouring(t_philo *philo)
{
	print_message(BRIGHT_YELLOW BOLD, "is eating", philo);
	pthread_mutex_lock(&philo->data->cemetary_mutex);
	philo->time_of_last_meal = get_time() - philo->data->starting_time;
	philo->time_of_starvation = philo->time_of_last_meal
		+ philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->cemetary_mutex);
	ft_sleep(philo->data->time_to_eat, philo);
	pthread_mutex_lock(&philo->data->food_mutex);
	if (philo->meals_eaten != -1)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->food_mutex);
}

void	returning_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_is_eating(t_philo *philo)
{
	if (is_dead(philo) == false || is_full(philo) == false)
		taking_forks(philo);
	if (is_dead(philo) == false || is_full(philo) == false)
		devouring(philo);
	returning_forks(philo);
}
