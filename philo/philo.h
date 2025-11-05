/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:36:18 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/05 11:49:40 by isastre-         ###   ########.fr       */
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
 * pthread_: create detach join;
 * pthread_mutex_: init destroy lock unlock
 */
# include <stdbool.h> // booleans

// ##### DEFINES #####

// printf
# define RESET "\033[0m"
# define RED "\033[1;31m"

// ##### STRUCTS #####

typedef pthread_mutex_t		t_lock;
typedef struct timeval		t_tv;
typedef struct s_monitor	t_monitor;
typedef struct s_fork		t_fork;
typedef struct s_philo		t_philo;

struct s_monitor
{
	// input data
	int		n_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals_limit; // [number_of_times_each_philosopher_must_eat]
	// forks, philos & locks
	t_fork	*forks;
	t_philo	*philos;
	t_lock	ready_lock;
	t_lock	print_lock;
	t_lock	end_lock;
	// simulation data
	bool	ready;
	long	start_time;
	bool	end; // true if philo dies or meals_limit is reached
};

struct s_fork
{
	int		id;
	t_lock	fork;
};

struct s_philo
{
	int			id; // starts at 0
	pthread_t	thread; // each philo is a thread
	// forks
	t_fork		*left_fork; // fork_id == id
	t_fork		*right_fork; // fork_id == id + 1
	// meals
	t_lock		meals_lock;
	long		last_meal; // timestamp when the philo had its last meal
	long		meals_eaten; // for [number_of_times_each_philosopher_must_eat]
	bool		full; // true when meals_eaten == meals_limit
	// monitor -> common data
	t_monitor	*monitor;
};

// ##### FUNCTIONS #####

#endif
