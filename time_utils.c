/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:06:15 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/03 11:31:27 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int miliseconds)
{
	usleep(miliseconds * 1000);
}

/**
 * @returns time in miliseconds
 */
int		ft_getms()
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int		ft_get_timestamp(t_monitor *monitor)
{
	return (ft_getms() - (monitor->start_time.tv_sec * 1000
		+ monitor->start_time.tv_usec / 1000));
}
