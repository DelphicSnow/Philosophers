/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:07:39 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/28 19:39:04 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	args_check(int argc, char **argv)
{
	int	i;
	int	nb;

	i = 1;
	while (i < argc)
	{
		if (is_digits(argv[i]) == false)
			return (printf(STR_VALID_INPUT), false);
		nb = ft_atoi(argv[i]);
		if (i == 1 && (nb <= 0 || nb > 200))
			return (printf(STR_PHILO_MAX), false);
		if (i != 1 && nb == -1)
			return (printf(STR_VALID_INPUT), false);
		i++;
	}
	return (true);
}
