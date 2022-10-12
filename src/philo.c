/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 17:03:02 by nphilipp      #+#    #+#                 */
/*   Updated: 2022/10/12 19:41:55 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*repeat(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	if (philo->times_eaten == 0 && !(philo->num % 2))
		usleep(2000);
	eat(philo);
	sleep_think(philo);
	if (*philo->info.alive == 0)
		return (0);
	pthread_mutex_lock(&philo->protect_eat);
	if (philo->info.often_to_eat == philo->times_eaten)
	{
		pthread_mutex_unlock(&philo->protect_eat);
		return (NULL); 
	}
	pthread_mutex_unlock(&philo->protect_eat);
	repeat(v_philo);
	return (NULL);
}

t_philo	*copy_info(t_info info, pthread_mutex_t **forks, int num)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (0); //add error
	philo->info = info;
	philo->num = num + 1;
	philo->fork_left = forks[num];
	if (num + 1 == info.number_philo)
		philo->fork_right = forks[0];
	else
		philo->fork_right = forks[num + 1];
	philo->dead = 0;
	philo->times_eaten = 0;
	philo->last_eaten = 0;
	pthread_mutex_init(&philo->protect_eat, NULL);
	return (philo);
}

pthread_mutex_t	**setup_forks(t_info info)
{
	int				i;
	pthread_mutex_t	**forks;

	forks = malloc(sizeof(pthread_mutex_t *) * info.number_philo);
	if (forks == NULL)
		return (NULL); //add error
	i = 0;
	while (i < info.number_philo)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (forks[i] == NULL)
			return (0); // ADD ERROR
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	return (forks);
}

void	thread_set_up(t_info info)
{
	pthread_t		*threads;
	t_philo			**philos;
	pthread_mutex_t	**forks;
	pthread_t		alive;
	int				i;

	threads = malloc(sizeof(pthread_t *) * (info.number_philo + 1));
	philos = malloc(sizeof(t_philo *) * info.number_philo);
	forks = setup_forks(info);
	if (threads == NULL || philos == NULL || forks == NULL)
		return ; //add error
	i = 0;
	while (i < info.number_philo)
	{
		philos[i] = copy_info(info, forks, i);
		pthread_create(&threads[i], NULL, &repeat, philos[i]);
		i++;
	}
	pthread_create(&alive, NULL, &check_if_alive, philos);
	i = 0;
	while (i < info.number_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac < 5)
		return (0); //error not enough variables
	if (check_variables(ac, av))
		return (0); //error none numiric variables
	info.number_philo = simp_atoi(av[1]);
	info.time_to_die = simp_atoi(av[2]);
	info.time_to_eat = simp_atoi(av[3]);
	info.time_to_sleep = simp_atoi(av[4]);
	if (ac >= 5)
		info.often_to_eat = simp_atoi(av[5]);
	else
		info.often_to_eat = -1;
	info.print = malloc(sizeof(pthread_mutex_t));
	info.alive = malloc(sizeof(int));
	if (info.print == NULL || info.alive == NULL)
		return (0);
	*info.alive = 1;
	pthread_mutex_init(info.print, NULL);
	gettimeofday(&info.start_time, NULL);
	thread_set_up(info);
	return (0);
}
