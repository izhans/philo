/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:46:37 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/09 09:21:50 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_take_fork(t_philo *philo, t_fork *fork);

bool	ft_eat(t_philo *philo)
{
	// take 1st fork
	if (!ft_take_fork(philo, philo->first_fork))
		return (false);
	// take 2nd fork
	if (!ft_take_fork(philo, philo->second_fork))
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		return (false);
	}
	// eat
	ft_print(philo, PHILO_EAT);
	ft_usleep(philo->monitor, philo->monitor->time_to_eat);
	// update vars
	if (!ft_end_dinner(philo->monitor))
	{
		pthread_mutex_lock(&philo->meals_lock);
		philo->last_meal = ft_getms();
		philo->meals_eaten++;
		// philo->full // ? tendria que cambiar ft_meals_limit_reached
		pthread_mutex_unlock(&philo->meals_lock);
	}
	// leave forks
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
	return (true);
}

bool	ft_sleep(t_philo *philo)
{
	if (ft_end_dinner(philo->monitor))
		return (false);
	ft_print(philo, PHILO_SLEEP);
	ft_usleep(philo->monitor, philo->monitor->time_to_sleep);
	return (true);
}

bool	ft_think(t_philo *philo)
{
	if (ft_end_dinner(philo->monitor))
		return (false);
	ft_print(philo, PHILO_THINK);
	// TODO apply fairness
	return (true);
}

/**
 * @brief takes a fork while checking the dinner is still going
 * @note in case the dinner ends, releases the fork that have just taked
 */
static bool	ft_take_fork(t_philo *philo, t_fork *fork)
{
	if (ft_end_dinner(philo->monitor))
		return (false);

	// take fork
	pthread_mutex_lock(&fork->fork);
	if (ft_end_dinner(philo->monitor))
	{
		pthread_mutex_unlock(&fork->fork);
		return (false);
	}
	ft_print(philo, PHILO_TAKE_FORK);
	return (true);
}