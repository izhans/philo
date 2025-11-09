/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:49:57 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/09 09:25:02 by isastre-         ###   ########.fr       */
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

/**
 * @brief prints take fork, waits time_to_die and prints death
 */
void	ft_one_philo_dinner(t_monitor *monitor)
{
	int	philo_id;

	philo_id = 1;
	printf("%d %d %s\n", 0, philo_id, PHILO_TAKE_FORK);
	ft_usleep(monitor, monitor->time_to_die);
	printf("%d %d %s\n", monitor->time_to_die, philo_id, PHILO_DIE);
}

/**
 * @brief creates philos and monitor threads, starts dinner and waits till end
 */
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
	// create monitor thread
	if (pthread_create(&monitor->thread, NULL,
			monitor_routine, monitor) != EXIT_SUCCESS)
		ft_exit(monitor, THREAD_INIT_ERROR, true);
	// set start time
	monitor->start_time = ft_getms();
	// set ready flag to true
	ft_setbool(&monitor->ready, true, &monitor->ready_lock);
	// join threads
	// ? primero monitor o philos
	ft_join_threads(monitor);
	pthread_join(monitor->thread, NULL);
}

/**
 * @brief while !end -> eat -> sleep -> think -> repeat
 */
void	*routine(void *data)
{
	t_philo		*philo;
	t_monitor	*monitor;

	philo = data;
	monitor = philo->monitor;
	// while !ready -> wait
	while (!ft_getbool(&monitor->ready, &monitor->ready_lock))
		usleep(CHECK_READY_ACTIVE_WAIT);
	// set last_meal to now
	ft_setlong(&philo->last_meal, ft_getms(), &philo->meals_lock);
	// think
	ft_print(philo, PHILO_THINK);
	// ? delay
	if (philo->id % 2 == 0)
		ft_usleep(monitor, monitor->time_to_eat / 2); // TODO elegir un tiempo en caso de que time_to_eat sea muy grande
	// while !end -> eat -> sleep -> think -> repeat
	while (!ft_end_dinner(monitor))
	{
		if (!ft_eat(philo) || !ft_sleep(philo) || !ft_think(philo))
			break ;
	}
	return (NULL);
}

/**
 * @brief check if philos are full or dead and sets flag end to true
 */
void	*monitor_routine(void *data)
{
	t_monitor	*monitor;

	monitor = data;
	while (!ft_getbool(&monitor->ready, &monitor->ready_lock))
		usleep(CHECK_READY_ACTIVE_WAIT);
	usleep(MONITOR_THREAD_DELAY);
	while (true)
	{
		if (ft_meals_limit_reached(monitor) || ft_a_philo_died(monitor))
			break ;
		usleep(CHECK_END_ACTIVE_WAIT);
	}
	ft_setbool(&monitor->end, true, &monitor->end_lock);
	return (NULL);
}
