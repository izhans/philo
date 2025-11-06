/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:13:58 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/06 13:25:01 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief exits with failure status, cleaning all and printing the given msg
 */
void	ft_exit(t_monitor *monitor, char *msg, bool destroy_locks)
{
	printf(RED "%s\n" RESET, msg);
	if (destroy_locks)
		ft_destroy_locks(monitor);
	ft_join_threads(monitor);
	ft_free_monitor(monitor);
	exit(EXIT_FAILURE);
}

/**
 * @brief destroys initialized locks
 */
void	ft_destroy_locks(t_monitor *monitor)
{
	int		i;
	bool	clear_all;

	i = 0;
	while (i < monitor->created_forks)
	{
		pthread_mutex_destroy(&monitor->forks[i].fork);
		i++;
	}
	clear_all = monitor->created_forks == monitor->n_philos;
	if (!clear_all)
		return ;
	pthread_mutex_destroy(&monitor->end_lock);
	pthread_mutex_destroy(&monitor->ready_lock);
	pthread_mutex_destroy(&monitor->print_lock);
	i = 0;
	while (i < monitor->created_philos)
	{
		pthread_mutex_destroy(&monitor->philos[i].meals_lock);
		i++;
	}
}

/**
 * @brief frees the allocated memory in monitor
 */
void	ft_free_monitor(t_monitor *monitor)
{
	if (!monitor)
		return ;
	if (monitor->forks)
		free(monitor->forks);
	if (monitor->philos)
		free(monitor->philos);
}

void	ft_join_threads(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->created_threads)
	{
		pthread_join(monitor->philos[i].thread, NULL);
		i++;
	}
}
