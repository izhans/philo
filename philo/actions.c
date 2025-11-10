/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:46:37 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/10 18:41:42 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_take_fork(t_philo *philo, t_fork *fork);

/**
 * @brief takes forks, eats, updates vars and leave forks,
 * all while checking dinner hasn't come to an end
 */
bool	ft_eat(t_philo *philo)
{
	if (!ft_take_fork(philo, philo->first_fork))
		return (false);
	if (!ft_take_fork(philo, philo->second_fork))
	{
		pthread_mutex_unlock(philo->first_fork);
		return (false);
	}
	ft_setlong(&philo->last_meal, ft_getms(), &philo->meals_lock);
	ft_print(philo, PHILO_EAT);
	ft_usleep(philo->monitor, philo->monitor->time_to_eat);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->monitor->meals_limit)
		ft_setbool(&philo->full, true, &philo->meals_lock);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
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
	pthread_mutex_lock(fork);
	if (ft_end_dinner(philo->monitor))
	{
		pthread_mutex_unlock(fork);
		return (false);
	}
	ft_print(philo, PHILO_TAKE_FORK);
	return (true);
}
