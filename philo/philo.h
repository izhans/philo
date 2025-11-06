/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:36:18 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/06 14:02:37 by isastre-         ###   ########.fr       */
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
# include <limits.h> // INT_MAX

// ##### DEFINES #####

// variables
# define MIN_INPUT_VALUE 1
# define MAX_INPUT_VALUE INT_MAX
# define MIN_MS 60
# define MAX_PHILOS 200
# define TIME_STEP 1000
# define SLEEP_STEP 500

// printf
# define RESET "\033[0m"
# define RED "\033[1;31m"

// actions
# define PHILO_TAKE_FORK "has taken a fork"
# define PHILO_EAT "is eating"
# define PHILO_SLEEP "is sleeping"
# define PHILO_THINK "is thinking"
# define PHILO_DIE "died"

// error msgs
# define INPUT_SIGNATURE "./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define INPUT_CONTAINS_INVALID_VALUES "Input must contain positive numeric (int)\
values with no more than 200 philos and no lower times than 60ms"
# define MALLOC_ERROR "An error ocurred while allocating memory"
# define MUTEX_INIT_ERROR "Error while initiating mutex"
# define THREAD_INIT_ERROR "Error while creating thread"
# define GETTIME_ERROR "Error while getting time of day"

// ##### STRUCTS #####

typedef pthread_mutex_t		t_lock;
typedef struct timeval		t_tv;
typedef struct s_monitor	t_monitor;
typedef struct s_fork		t_fork;
typedef struct s_philo		t_philo;

struct s_monitor
{
	// input data
	int			n_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_limit; // [number_of_times_each_philosopher_must_eat]
	// forks, philos & locks
	t_fork		*forks;
	t_philo		*philos;
	t_lock		ready_lock;
	t_lock		print_lock;
	t_lock		end_lock;
	// simulation data
	bool		ready;
	long		start_time;
	bool		end; // true if philo dies or meals_limit is reached
	// created data
	int			created_forks;
	int			created_philos;
	int			created_threads;
	// thread
	pthread_t	thread;
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

// parse & init
void	ft_parse_input(t_monitor *monitor, int argc, char *argv[]);
void	ft_init_structs(t_monitor *monitor);

// utils
void	ft_exit(t_monitor *monitor, char *msg, bool destroy_locks);
void	ft_free_monitor(t_monitor *monitor);
void	ft_destroy_locks(t_monitor *monitor);
void	ft_join_threads(t_monitor *monitor);

// time utils
void	ft_usleep(int miliseconds);
long	ft_elapsed_ms(long start);
long	ft_getms(void);

// getters & setters
bool	ft_getbool(bool *var, t_lock *lock);
void	ft_setbool(bool *var, bool value, t_lock *lock);
long	ft_getlong(long *var, t_lock *lock);
void	ft_setlong(long *var, long value, t_lock *lock);

#endif
