/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:46:35 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/06 18:33:14 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief checks if all the philos are full
 * @note philos are full if meals_limit has been reached on all of them
 * @returns true if there is a meal limit and all philos have reached it
 */
bool	ft_meals_limit_reached(t_monitor *monitor)
{
	int		i;
	long	meals_eaten;

	i = 0;
	if (monitor->meals_limit == 0)
		return (false);
	while (i < monitor->n_philos)
	{
		meals_eaten = ft_getlong(&monitor->philos[i].meals_eaten,
				&monitor->philos[i].meals_lock);
		if (meals_eaten < monitor->meals_limit)
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief checks if any philo has died
 * @note a philo is dead if now - last_meal >= time_to_die
 */
bool	ft_a_philo_died(t_monitor *monitor)
{
	int			i;
	long		last_meal;

	i = 0;
	while (i < monitor->n_philos)
	{
		last_meal = ft_getlong(&monitor->philos[i].last_meal,
				&monitor->philos[i].meals_lock);
		if (ft_getms() - last_meal >= monitor->time_to_die)
		{
			ft_print(&monitor->philos[i], PHILO_DIE);
			return (true);
		}
		i++;
	}
	return (false);
}
