/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:50:04 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/01 13:48:28 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_threads(t_monitor *monitor);
void	*routine(void *data);
void	ft_wait(t_monitor *monitor);
void	ft_finish(t_monitor *monitor);

int	main(int argc, char *argv[])
{
	t_monitor	monitor; // memoria no dinamica -> no hay que hacerle free :) ! pero a los malloc que se hagan por dentro si 

	// 1. validate & parse input
	ft_parse_input(&monitor, argc, argv);

	// 2. init data
	ft_init_structs(&monitor);
	
	// 3. philos do things
	if (monitor.n_philos == 1)
		return (ft_one_philo_dinner(&monitor), 0);
	ft_create_threads(&monitor);
	
	// 4. end -> clean + exit
	ft_finish(&monitor);

	return (0);
}

/**
 * @brief creates threads and sends the ready signal
 */
void	ft_create_threads(t_monitor *monitor)
{
	int	i;
	
	i = 0;
	// create threads -> this call routine
	while (i < monitor->n_philos)
	{
		pthread_create(&monitor->philos[i].thread, NULL, routine, &monitor->philos[i]); // TODO check error
		i++;
	}
	// set start_time
	gettimeofday(&monitor->start_time, NULL);
	// flag for starting routine
	ft_setbool(&monitor->ready, true, &monitor->locks->ready);
}

void	*routine(void *data)
{
	t_philo		*philo;
	t_monitor	*monitor;

	philo = (t_philo *) data;
	monitor = philo->monitor;
	ft_wait(monitor);
	// TODO philos algorithm
	ft_print(philo, THINK);
	if (philo->id % 2 == 1) // delay para los pares (id impreso)
		ft_usleep(monitor->time_to_eat / 2);
	ft_dinner(monitor, philo);
	return (NULL);
}

void	ft_wait(t_monitor *monitor)
{
	while (true)
	{
		if (ft_getbool(monitor->ready, &(monitor->locks->ready)))
			break;
		usleep(100); // TODO elegir cuanto tiempo
	}
}

/**
 * @brief waits for threads, destroy mutexes and frees allocated memory
 */
void	ft_finish(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->n_philos)
	{
		pthread_join(monitor->philos[i].thread, NULL);
		i++;
	}
	ft_destroy_locks(monitor);
	ft_free_monitor(monitor);
}
