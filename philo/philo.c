/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:49:57 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/06 08:54:51 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_monitor	monitor; // memoria no dinamica -> no hay que hacerle free :) ! pero a los malloc que se hagan por dentro si
	
	memset(&monitor, 0, sizeof(t_monitor));
	// 1. validate & parse input
	ft_parse_input(&monitor, argc, argv);
	// 2. init data
	ft_init_structs(&monitor);
	// 3. philos do things
	// 3.1 one philo case -> let die and end simulation
	// 3.2 create threads
	
	// 4. end -> wait threads and clean
	ft_destroy_locks(&monitor);
	ft_free_monitor(&monitor);
	return (0);
}
