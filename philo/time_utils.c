/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:39:49 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/07 11:15:39 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief sleeps in milis
 */
void	ft_usleep(t_monitor *monitor, int miliseconds)
{
	long	start;

	start = ft_getms();
	while (ft_elapsed_ms(start) < miliseconds)
	{
		if (ft_end_dinner(monitor))
			break ;
		usleep(SLEEP_STEP);
	}
}

/**
 * @brief calcs the elapsed time from start
 * @returns the elapsed time between the start and now
 */
long	ft_elapsed_ms(long start)
{
	return (ft_getms() - start);
}

/**
 * @returns current timestamp in miliseconds
 * @note:	1 second = 1000 miliseconds
 * 			1 milisecond = 1000 microseconds | 1 microsecond = 1/1000 miliseconds
 */
long	ft_getms(void)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * TIME_STEP + tv.tv_usec / TIME_STEP);
}
