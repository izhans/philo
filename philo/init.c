/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:21:44 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/09 13:44:43 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_alloc_structs(t_monitor *monitor);
static bool	ft_init_locks(t_monitor *monitor);
static bool	ft_init_philos(t_monitor *monitor);
static void	ft_assign_forks(t_philo *philo, int id);

/**
 * @brief creates the forks and philos
 */
bool	ft_init_structs(t_monitor *monitor)
{
	monitor->ready = false;
	monitor->end = false;
	return (ft_alloc_structs(monitor) && ft_init_locks(monitor)
		&& ft_init_philos(monitor));
}

static bool	ft_alloc_structs(t_monitor *monitor)
{
	monitor->philos = malloc(monitor->n_philos * sizeof(t_philo));
	monitor->forks = malloc(monitor->n_philos * sizeof(t_fork));
	if (monitor->philos == NULL || monitor->forks == NULL)
		return (ft_exit(monitor, MALLOC_ERROR, false, false));
	return (true);
}

/**
 * @brief inits forks & locks (all mutexes)
 */
static bool	ft_init_locks(t_monitor *monitor)
{
	int		i;

	i = 0;
	if (pthread_mutex_init(&monitor->ready_lock, NULL) == EXIT_SUCCESS)
		monitor->created_ready = true;
	if (pthread_mutex_init(&monitor->end_lock, NULL) == EXIT_SUCCESS)
		monitor->created_end = true;
	if (pthread_mutex_init(&monitor->print_lock, NULL) == EXIT_SUCCESS)
		monitor->created_print = true;
	if (!monitor->created_ready || !monitor->created_end
		|| !monitor->created_print)
		return (ft_exit(monitor, MUTEX_INIT_ERROR, true, false));
	while (i < monitor->n_philos)
	{
		monitor->forks[i].id = i;
		if (pthread_mutex_init(&monitor->forks[i].fork, NULL) != EXIT_SUCCESS)
			return (ft_exit(monitor, MUTEX_INIT_ERROR, true, false));
		monitor->created_forks++;
		i++;
	}
	return (true);
}

/**
 * @brief inits all philos data except the thread
 */
static bool	ft_init_philos(t_monitor *monitor)
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
		ft_assign_forks(philo, i);
		if (pthread_mutex_init(&philo->meals_lock, NULL) != EXIT_SUCCESS)
			return (ft_exit(monitor, MUTEX_INIT_ERROR, true, false));
		monitor->created_philos++;
		i++;
	}
	return (true);
}

static void	ft_assign_forks(t_philo *philo, int id)
{
	if (id % 2 == 0)
	{
		philo->first_fork = philo->left_fork;
		philo->second_fork = philo->right_fork;
	}
	else
	{
		philo->first_fork = philo->right_fork;
		philo->second_fork = philo->left_fork;
	}
}
