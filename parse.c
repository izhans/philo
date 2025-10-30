/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:21:29 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/30 13:55:37 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		ft_atoi(char *str);
static bool		ft_isspace(int c);
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
	monitor->n_philos = ft_atoi(argv[1]);
	monitor->time_to_die = ft_atoi(argv[2]);
	monitor->time_to_eat = ft_atoi(argv[3]);
	monitor->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		monitor->meals_limit = ft_atoi(argv[5]);
	else
		monitor->meals_limit = 0;
}

static int	ft_atoi(char *str)
{
	long	n;

	n = 0;
	while (ft_isspace(*str))
		str++;
	if (ft_strlen(str) > 10 || *str == '-')
		ft_exit(INPUT_CONTAINS_INVALID_VALUES);
	if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	if (n > MAX_INPUT_VALUE || n < MIN_INPUT_VALUE)
		ft_exit(INPUT_CONTAINS_INVALID_VALUES);
	return (n);
}

static bool	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
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
