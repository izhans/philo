/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:02:13 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/31 20:39:03 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief allocates and inits locks
 */
void	ft_create_locks(t_monitor *monitor)
{
	monitor->locks = ft_malloc(sizeof(t_locks));
	pthread_mutex_init(&monitor->locks->ready, NULL); // TODO check error
}

/**
 * @brief destroy locks
 */
void	ft_destroy_locks(t_monitor *monitor)
{
	t_locks	*locks;

	locks = monitor->locks;
	pthread_mutex_destroy(&locks->ready);
}
