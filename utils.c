/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:00:05 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/01 11:56:01 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc(size_t size)
{
	// TODO free all
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		ft_exit(MALLOC_ERROR);
	return (ret);
}

void	ft_exit(char *msg)
{
	printf(RED "%s\n" RESET, msg);
	// TODO free + clean
	exit(EXIT_FAILURE);
}

void	ft_free_monitor(t_monitor *monitor)
{
	if (!monitor)
		return ;
	if (monitor->forks)
		free(monitor->forks);
	if (monitor->philos)
		free(monitor->philos);
	if (monitor->locks)
		free(monitor->locks);
}

void	ft_print(t_philo *philo, char *action)
{
	t_lock *lock;
	
	lock = &(philo->monitor->locks->print);
	pthread_mutex_lock(lock);
	printf("%d %s\n", philo->id, action); // TODO añadir timestamp
	pthread_mutex_unlock(lock);
}

void	ft_sleep(int ms)
{
	usleep(ms * 1000);
}
