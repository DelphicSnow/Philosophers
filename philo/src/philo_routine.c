/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:26:33 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/28 20:03:42 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
checks if any philosopher has died. If true, the thread is terminated
*/
bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->cemetary_mutex);
	if (philo->data->first_death == true)
	{
		pthread_mutex_unlock(&philo->data->cemetary_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->cemetary_mutex);
	return (false);
}

void	philo_is_sleeping(t_philo *philo)
{
	print_message(CYAN, "is sleeping", philo);
	ft_sleep(philo->data->time_to_sleep, philo);
}

/*
It calculates the time the philo should spend thinking
to prevent one philo thread being prioritized and blocking other threads.
Thanks Mia Combeau for this solution. 
*/
void	philo_is_thinking(t_philo *philo, bool start)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->data->food_mutex);
	time_to_think = (philo->data->time_to_die
			- (get_time() - philo->data->starting_time
				- philo->time_of_last_meal)
			- philo->data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->data->food_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && start == true)
		time_to_think = 1;
	if (time_to_think > 200)
		time_to_think = 200;
	if (start == false)
		print_message(WHITE, "is thinking", philo);
	ft_sleep(time_to_think, philo);
}

/*
Routine for single philo to avoid waiting for second fork.
*/
void	*lone_philo_rtn(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	philo->time_of_last_meal = philo->data->starting_time;
	pthread_mutex_lock(philo->right_fork);
	print_message(YELLOW, "has taken a fork", philo);
	ft_sleep(philo->data->time_to_die, philo);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

void	*philo_rtn(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if ((philo->name % 2) > 0)
		philo_is_thinking(philo, true);
	while (is_dead(philo) == false && is_full(philo) == false)
	{
		philo_is_eating(philo);
		if (is_dead(philo) || is_full(philo))
			return (NULL);
		philo_is_sleeping(philo);
		if (is_dead(philo) || is_full(philo))
			return (NULL);
		philo_is_thinking(philo, false);
	}
	return (NULL);
}
