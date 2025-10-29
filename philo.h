/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 07:42:17 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/29 11:22:25 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

// ##### INCLUDES #####

# include <stdio.h> // printf
# include <string.h> // memset
# include <stdlib.h> // malloc free
# include <unistd.h> // write usleep
# include <sys/time.h> // gettimeofday
# include <pthread.h> // threads & mutexes
/**
 * pthread_: create _detach _join;
 * pthread_mutex_: init destroy lock unlock
 */
# include <stdbool.h> // booleans

// ##### STRUCTS #####

typedef pthread_mutex_t		t_lock;
typedef struct s_monitor	t_monitor;
typedef struct s_fork		t_fork;
typedef struct s_philo		t_philo;

struct s_monitor
{
	// input data
	int		n_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals_limit; // [number_of_times_each_philosopher_must_eat]
	// forks & philos
	t_fork	*forks;
	t_philo	*philos;
	// simulation data
	int		start_time;
	bool	end; // true if philo dies or meals_limit is reached
};
struct s_fork
{
	int		id;
	t_lock	fork;
};

struct s_philo
{
	int			id;
	pthread_t	thread; // each philo is a thread
	t_fork		*left_fork;
	t_fork		*right_fork;
	int			last_meal; // when did the philo had its last meal
	int			meals_eaten; // for [number_of_times_each_philosopher_must_eat]
	bool		full; // meals_eaten == meals_limit
	t_monitor	*monitor;
};

#endif
