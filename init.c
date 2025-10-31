/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:19:33 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/31 19:03:11 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_init_philos(t_monitor *monitor);

/**
 * @brief creates the forks and philos
 */
void	ft_init_structs(t_monitor *monitor)
{
	int		i;

	i = 0;
	monitor->philos = ft_malloc(monitor->n_philos * sizeof(t_philo));
	monitor->forks = ft_malloc(monitor->n_philos * sizeof(t_fork));
	monitor->ready = false;
	monitor->end = false;
	while (i < monitor->n_philos)
	{
		monitor->forks[i].id = i;
		pthread_mutex_init(&monitor->forks[i].fork, NULL); // TODO check error
		i++;
	}
	ft_create_locks(monitor);
	ft_init_philos(monitor);
}

/**
 * @brief inits all philos data
 */
static void	ft_init_philos(t_monitor *monitor)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < monitor->n_philos)
	{
		philo = &monitor->philos[i];
		philo->monitor = monitor;
		philo->id = i;
		philo->full = false;
		philo->meals_eaten = 0;
		philo->last_meal = 0;
		philo->left_fork = &monitor->forks[i];
		philo->right_fork = &monitor->forks[(i +1) % monitor->n_philos];
		i++;
	}
}
