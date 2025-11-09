/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:21:44 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/07 13:44:48 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_malloc(t_monitor *monitor, size_t size);
static void	ft_init_locks(t_monitor *monitor);
static void	ft_init_philos(t_monitor *monitor);
static void	ft_assign_forks(t_philo *philo, int id); 

/**
 * @brief creates the forks and philos
 */
void	ft_init_structs(t_monitor *monitor)
{
	monitor->philos = ft_malloc(monitor, monitor->n_philos * sizeof(t_philo));
	monitor->forks = ft_malloc(monitor, monitor->n_philos * sizeof(t_fork));
	monitor->ready = false;
	monitor->end = false;
	ft_init_locks(monitor);
	ft_init_philos(monitor);
}

static void	*ft_malloc(t_monitor *monitor, size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		ft_exit(monitor, MALLOC_ERROR, false);
	return (ret);
}

/**
 * @brief inits forks & locks (all mutexes)
 */
static void	ft_init_locks(t_monitor *monitor)
{
	int		i;

	i = 0;
	if (pthread_mutex_init(&monitor->ready_lock, NULL) != EXIT_SUCCESS)
		ft_exit(monitor, MUTEX_INIT_ERROR, false);
	if (pthread_mutex_init(&monitor->end_lock, NULL) != EXIT_SUCCESS)
	{
		pthread_mutex_destroy(&monitor->ready_lock);
		ft_exit(monitor, MUTEX_INIT_ERROR, false);
	}
	if (pthread_mutex_init(&monitor->print_lock, NULL) != EXIT_SUCCESS)
	{
		pthread_mutex_destroy(&monitor->ready_lock);
		pthread_mutex_destroy(&monitor->end_lock);
		ft_exit(monitor, MUTEX_INIT_ERROR, false);
	}
	while (i < monitor->n_philos)
	{
		monitor->forks[i].id = i;
		if (pthread_mutex_init(&monitor->forks[i].fork, NULL) != EXIT_SUCCESS)
			ft_exit(monitor, MUTEX_INIT_ERROR, false);
		monitor->created_forks++;
		i++;
	}
}

/**
 * @brief inits all philos data except the thread
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
		ft_assign_forks(philo, i);
		if (pthread_mutex_init(&philo->meals_lock, NULL) != EXIT_SUCCESS)
			ft_exit(monitor, MUTEX_INIT_ERROR, true);
		monitor->created_philos++;
		i++;
	}
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
