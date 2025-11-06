/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:49:57 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/06 13:36:52 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_one_philo_dinner(t_monitor *monitor);
void	ft_create_threads(t_monitor *monitor);
void	*routine(void *data);
void	*monitor_routine(void *data);

int	main(int argc, char *argv[])
{
	t_monitor	monitor;

	memset(&monitor, 0, sizeof(t_monitor));
	// 1. validate & parse input
	ft_parse_input(&monitor, argc, argv);
	// 2. init data
	ft_init_structs(&monitor);
	// 3. philos do things
	// 3.1 one philo case -> let die and end simulation
	if (monitor.n_philos == 1)
		ft_one_philo_dinner(&monitor);
	// 3.2 create threads
	else
		ft_create_threads(&monitor);
	// 4. end -> wait threads and clean
	ft_destroy_locks(&monitor);
	ft_free_monitor(&monitor);
	return (0);
}

void	ft_one_philo_dinner(t_monitor *monitor)
{
	int	philo_id;

	philo_id = 1;
	printf("%d %d %s\n", 0, philo_id, PHILO_TAKE_FORK);
	// sleep monitor->time_to_die // TODO
	printf("%d %d %s\n", monitor->time_to_die, philo_id, PHILO_DIE);
}

void	ft_create_threads(t_monitor *monitor)
{
	int	i;

	i = 0;
	// create threads
	while (i < monitor->n_philos)
	{
		if (pthread_create(&monitor->philos[i].thread, NULL,
				routine, &monitor->philos[i]) != EXIT_SUCCESS)
			ft_exit(monitor, THREAD_INIT_ERROR, true);
		monitor->created_threads++;
		i++;
	}
	// set start time
	// monitor->start_time = now; // TODO
	// create monitor thread
	if (pthread_create(&monitor->thread, NULL,
			monitor_routine, &monitor->philos[i]) != EXIT_SUCCESS)
		ft_exit(monitor, THREAD_INIT_ERROR, true);
	// set ready flag to true
	pthread_mutex_lock(&monitor->ready_lock);
	monitor->ready = true;
	pthread_mutex_unlock(&monitor->ready_lock);
	// join threads
	// ? primero monitor o philos
	ft_join_threads(monitor);
	pthread_join(monitor->thread, NULL);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	(void) philo;
	// TODO
	// while !ready -> wait
	// set last_meal to now
	// think
	// while !end -> eat -> sleep -> think -> repeat
	return (NULL);
}

void	*monitor_routine(void *data)
{
	t_monitor	*monitor;

	monitor = data;
	(void) monitor;
	// TODO
	// check if meals_limit has been reached on all philos
	// check no philo is dead (if now - last_meal >= time_to_die, is dead)
	return (NULL);
}
