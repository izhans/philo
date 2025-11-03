/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 10:48:03 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/03 11:31:06 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	ft_eat(t_philo *philo);
static	void	ft_sleep(t_philo *philo);
static	void	ft_think(t_philo *philo);

void	ft_one_philo_dinner(t_monitor *monitor)
{
	int	philo_id;

	philo_id = 1;
	printf("%d %d %s\n", 0, philo_id, TAKE_FORK);
	ft_usleep(monitor->time_to_die);
	printf("%d %d %s\n", monitor->time_to_die, philo_id, DIE);
	ft_free_monitor(monitor);
}

void	ft_dinner(t_monitor *monitor, t_philo *philo)
{
	while (!ft_getbool(monitor->end, &(monitor->locks->end)))
	{
		if (philo->full)
			break;
		
		// eat
		ft_eat(philo);
		// sleep
		ft_sleep(philo);
		// think
		ft_think(philo);
	}
}

static	void	ft_eat(t_philo *philo)
{
	// take forks
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->right_fork->fork);
	// eat
	ft_print(philo, EAT);
	ft_usleep(philo->monitor->time_to_eat);
	// release forks
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	// update philo->meals_eaten & philo->last_meal
}

static	void	ft_sleep(t_philo *philo)
{
	ft_print(philo, SLEEP);
	ft_usleep(philo->monitor->time_to_sleep);
}

static	void	ft_think(t_philo *philo)
{
	ft_print(philo, THINK);
}
