/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:49:36 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/28 19:57:06 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mutex_cide(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->time_mutex);
	pthread_mutex_destroy(&data->food_mutex);
	pthread_mutex_destroy(&data->cemetary_mutex);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
		i++;
	}
	free(data->fork_mutex);
}

/* custom sleep function which is sensitive to philo death. */
void	ft_sleep(int time_to, t_philo *philo)
{
	time_t	start;

	start = get_time();
	while ((get_time() - start) < time_to && is_dead(philo) == false)
		usleep(50);
}

int	ft_atoi(char *str)
{
	unsigned long long	nb;
	int					i;

	i = 0;
	nb = 0;
	if (str == NULL)
		return (-1);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

/* sec are converted to millisecs + microsecs are converted to millisecs*/
time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_message(char	*colour, char *str, t_philo *philo)
{
	if (!is_dead(philo))
	{
		pthread_mutex_lock(&philo->data->time_mutex);
		printf("%s%ld %d %s" RESET "\n", colour, get_time() 
			- philo->data->starting_time, philo->name, str);
		pthread_mutex_unlock(&philo->data->time_mutex);
	}
}
