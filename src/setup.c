/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 15:18:39 by nphilipp      #+#    #+#                 */
/*   Updated: 2022/10/12 15:48:39 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	give_time(t_info info)
{
	int				time;
	struct timeval	now_time;

	gettimeofday(&now_time, NULL);
	time = (((now_time.tv_sec - info.start_time.tv_sec) * 1000) + \
		((now_time.tv_usec - info.start_time.tv_usec) / 1000));
	return (time);
}

static int	check_if_num(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] < '0' || string[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	simp_atoi(char *string)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (string == NULL)
		return (0);
	while (string[i])
	{
		num += string[i] - '0';
		i++;
		if (string[i])
			num *= 10;
	}
	return (num);
}

int	check_variables(int varcount, char **vars)
{
	int	i;

	i = 1;
	while (i < varcount && i < 7)
	{
		if (check_if_num(vars[i]))
			return (1);
		i++;
	}
	return (0);
}
