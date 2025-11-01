/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 10:48:03 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/01 12:01:01 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_one_philo_dinner(t_monitor *monitor)
{
	int	philo_id;

	philo_id = 1;
	printf("%d %d %s\n", 0, philo_id, TAKE_FORK);
	ft_sleep(monitor->time_to_die);
	printf("%d %d %s\n", monitor->time_to_die, philo_id, DIE);
	ft_free_monitor(monitor);
}
