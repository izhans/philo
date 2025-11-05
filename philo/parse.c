/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:21:29 by isastre-          #+#    #+#             */
/*   Updated: 2025/11/05 12:12:08 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		ft_atoi(char *str, int min, int max);
static size_t	ft_strlen(char *s);
static bool		ft_isdigit(int c);

/**
 * @brief checks argc is 5 or 6 and parses input into numbers
 * that must be between MIN_INPUT_VALUE and MAX_INPUT_VALUE (both included)
 * @note in case of error, exit is performed
 */
void	ft_parse_input(t_monitor *monitor, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		ft_exit(INPUT_SIGNATURE);
	monitor->n_philos = ft_atoi(argv[1], MIN_INPUT_VALUE, MAX_PHILOS);
	monitor->time_to_die = ft_atoi(argv[2], MIN_MS, MAX_INPUT_VALUE);
	monitor->time_to_eat = ft_atoi(argv[3], MIN_MS, MAX_INPUT_VALUE);
	monitor->time_to_sleep = ft_atoi(argv[4], MIN_MS, MAX_INPUT_VALUE);
	if (argv[5])
		monitor->meals_limit
			= ft_atoi(argv[5], MIN_INPUT_VALUE, MAX_INPUT_VALUE);
	else
		monitor->meals_limit = 0;
}

static int	ft_atoi(char *str, int min, int max)
{
	long	n;

	n = 0;
	if (ft_strlen(str) > 10 || *str == '-')
		ft_exit(INPUT_CONTAINS_INVALID_VALUES);
	if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	if (n > max || n < min)
		ft_exit(INPUT_CONTAINS_INVALID_VALUES);
	return (n);
}

static size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
