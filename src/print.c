/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 15:56:10 by nphilipp      #+#    #+#                 */
/*   Updated: 2022/10/12 19:14:33 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	print_action(t_philo *philo, int sort)
{
	pthread_mutex_lock(philo->info.print);
	if (*philo->info.alive == 1)
	{
		if (sort == 0)
			printf("%i %i has taken a fork\n", \
				give_time(philo->info), philo->num);
		else if (sort == 1)
			printf("%i %i is eating\n", give_time(philo->info), philo->num);
		else if (sort == 2)
			printf("%i %i is sleeping\n", give_time(philo->info), philo->num);
		else if (sort == 3)
			printf("%i %i is thinking\n", give_time(philo->info), philo->num);
	}
	pthread_mutex_unlock(philo->info.print);
	return (0);
}
