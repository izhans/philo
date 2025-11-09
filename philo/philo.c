/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:49:57 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/09 23:28:38 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_one_philo_dinner(t_monitor *monitor);
bool	ft_create_threads(t_monitor *monitor);
void	*routine(void *data);
void	*monitor_routine(void *data);

/**
 * @brief 
 * 1. validate & parse input
 * 2. inits data
 * 3. philos do things -> one philo or threads
 * 4. clean
 */
int	main(int argc, char *argv[])
{
	t_monitor	monitor;

	memset(&monitor, 0, sizeof(t_monitor));
	if (!ft_parse_input(&monitor, argc, argv) || !ft_init_structs(&monitor))
		return (1);
	if (monitor.n_philos == 1)
		ft_one_philo_dinner(&monitor);
	else if (!ft_create_threads(&monitor))
		return (1);
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
bool	ft_create_threads(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->n_philos)
	{
		if (pthread_create(&monitor->philos[i].thread, NULL,
				routine, &monitor->philos[i]) != EXIT_SUCCESS)
			return (ft_exit(monitor, THREAD_INIT_ERROR, true, true));
		monitor->created_threads++;
		i++;
	}
	if (pthread_create(&monitor->thread, NULL,
			monitor_routine, monitor) != EXIT_SUCCESS)
	{
		ft_setbool(&monitor->end, true, &monitor->end_lock);
		ft_setbool(&monitor->ready, true, &monitor->ready_lock);
		return (ft_exit(monitor, THREAD_INIT_ERROR, true, true));
	}
	monitor->start_time = ft_getms();
	ft_setbool(&monitor->ready, true, &monitor->ready_lock);
	ft_join_threads(monitor);
	pthread_join(monitor->thread, NULL);
	return (true);
}

/**
 * @brief waits for the ready flag, applies fairness and then 
 * 		while !end -> eat -> sleep -> think -> repeat
 */
void	*routine(void *data)
{
	t_philo		*philo;
	t_monitor	*monitor;

	philo = data;
	monitor = philo->monitor;
	while (!ft_getbool(&monitor->ready, &monitor->ready_lock))
		usleep(CHECK_READY_ACTIVE_WAIT);
	if (ft_end_dinner(monitor))
		return (NULL);
	ft_setlong(&philo->last_meal, ft_getms(), &philo->meals_lock);
	ft_print(philo, PHILO_THINK);
	ft_delay(philo);
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
	return (NULL);
}
