/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alive.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 17:59:49 by nphilipp      #+#    #+#                 */
/*   Updated: 2022/10/12 19:36:50 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int		has_died(t_philo *philo)
{
	int current_time;

	current_time = give_time(philo->info);
	pthread_mutex_lock(&philo->protect_eat);
	if (philo->info.time_to_die < (current_time - philo->last_eaten))
	{
		if (philo->times_eaten == philo->info.often_to_eat)
			return (0);
		pthread_mutex_unlock(&philo->protect_eat);
		*philo->info.alive = 0;
		printf("%i %i has died\n", current_time, philo->num);
		pthread_mutex_unlock(philo->info.print);
		return (1);
	}
	pthread_mutex_unlock(&philo->protect_eat);
	return (0);
}

void	*check_if_alive(void *v_philos)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = (t_philo **)v_philos;
	while (1)
	{
		while (i < philos[0]->info.number_philo)
		{
			if (has_died(philos[i]))
			{
				return (0);
			}
			i++;
		}
		i = 0;
	}
	return (0);
}
