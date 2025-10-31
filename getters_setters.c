/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:44:41 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/31 15:43:13 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_getbool(bool var, t_lock *lock)
{
	bool	value;

	pthread_mutex_lock(lock);
	value = var;
	pthread_mutex_unlock(lock);
	return (value);
}

void	ft_setbool(bool *var, bool value, t_lock *lock)
{
	pthread_mutex_lock(lock);
	*var = value;
	pthread_mutex_unlock(lock);
}
