/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 07:42:17 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/31 20:56:11 by isastre-         ###   ########.fr       */
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
# include <limits.h> // INT_MAX

// ##### DEFINES #####

// variables
# define MIN_INPUT_VALUE 1
# define MAX_INPUT_VALUE INT_MAX

// printf
# define RESET "\033[0m"
# define RED "\033[1;31m"

// error msgs
# define INPUT_SIGNATURE "./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define INPUT_CONTAINS_INVALID_VALUES "Input must contain positive numeric values \
between 1 and 2147483647 (both included)"
# define MALLOC_ERROR "An error ocurred while allocating memory"

// ##### STRUCTS #####

typedef pthread_mutex_t		t_lock;
typedef struct timeval		t_tv;
typedef struct s_monitor	t_monitor;
typedef struct s_fork		t_fork;
typedef struct s_locks		t_locks;
typedef struct s_philo		t_philo;

struct s_monitor
{
	// input data
	int		n_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals_limit; // [number_of_times_each_philosopher_must_eat]
	// forks & philos
	t_fork	*forks;
	t_philo	*philos;
	t_locks	*locks;
	// simulation data
	bool	ready;
	t_tv	start_time;
	bool	end; // true if philo dies or meals_limit is reached
};

struct s_fork
{
	int		id;
	t_lock	fork;
};

struct s_locks
{
	t_lock	ready;
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

// ##### FUNCTIONS #####

//parse
void	ft_parse_input(t_monitor *monitor, int argc, char *argv[]);

// init
void	ft_init_structs(t_monitor *monitor);

// mutexes
void	ft_create_locks(t_monitor *monitor);
void	ft_destroy_locks(t_monitor *monitor);

// utils
void	ft_exit(char *msg);
void	*ft_malloc(size_t size);
void	ft_free_monitor(t_monitor *monitor);

// getters & setters
bool	ft_getbool(bool var, t_lock *lock);
void	ft_setbool(bool *var, bool value, t_lock *lock);

#endif
