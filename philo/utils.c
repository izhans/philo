/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:13:58 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/09 14:19:43 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief exits with failure status, cleaning all and printing the given msg
 */
bool	ft_exit(t_monitor *monitor, char *msg, bool destroy_locks,
		bool join_threads)
{
	printf(RED "%s\n" RESET, msg);
	if (destroy_locks)
		ft_destroy_locks(monitor);
	if (join_threads)
		ft_join_threads(monitor);
	ft_free_monitor(monitor);
	return (false);
}

/**
 * @brief destroys initialized locks
 */
void	ft_destroy_locks(t_monitor *monitor)
{
	int		i;

	i = 0;
	while (i < monitor->created_forks)
	{
		pthread_mutex_destroy(&monitor->forks[i].fork);
		i++;
	}
	if (monitor->created_end)
		pthread_mutex_destroy(&monitor->end_lock);
	if (monitor->created_ready)
		pthread_mutex_destroy(&monitor->ready_lock);
	if (monitor->created_print)
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

void	ft_print(t_philo *philo, char *action)
{
	t_monitor	*monitor;
	long		timestamp;

	monitor = philo->monitor;
	pthread_mutex_lock(&monitor->print_lock);
	timestamp = ft_elapsed_ms(monitor->start_time);
	if (!ft_end_dinner(monitor))
		printf("%ld %d %s\n", timestamp, philo->id, action); // TODO id+1
	pthread_mutex_unlock(&monitor->print_lock);
}
