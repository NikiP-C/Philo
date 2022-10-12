/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Activities.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 15:38:42 by nphilipp      #+#    #+#                 */
/*   Updated: 2022/10/12 19:38:28 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_philo *philo)
{
	int	start_eating;

	if (*philo->info.alive == 0)
		return ;
	pthread_mutex_lock(philo->fork_left);
	print_action(philo, 0);
	pthread_mutex_lock(philo->fork_right);
	print_action(philo, 0);
	start_eating = give_time(philo->info);
	print_action(philo, 1);
	pthread_mutex_lock(&philo->protect_eat);
	philo->times_eaten++;
	philo->last_eaten = give_time(philo->info);
	pthread_mutex_unlock(&philo->protect_eat);
	while (start_eating + philo->info.time_to_eat > give_time(philo->info))
		usleep(500);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	sleep_think(t_philo *philo)
{
	int	start_sleeping;

	if (*philo->info.alive == 0)
		return ;
	print_action(philo, 2);
	start_sleeping = give_time(philo->info);
	while ((start_sleeping + philo->info.time_to_sleep) \
		> give_time(philo->info))
		usleep(500);
	print_action(philo, 3);
}
