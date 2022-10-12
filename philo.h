/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 17:13:09 by nphilipp      #+#    #+#                 */
/*   Updated: 2022/10/12 11:44:37 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_info
{
	struct timeval	start_time;
	int				number_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				often_to_eat;
	pthread_mutex_t	*print;
	int				*alive;
}				t_info;

typedef struct s_philo
{
	t_info			info;
	int				num;
	int				last_eaten;
	int				times_eaten;
	int				dead;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	protect_eat;
}				t_philo;

int		check_variables(int varcount, char **vars);
int		simp_atoi(char *string);
int		give_time(t_info info);
void	eat(t_philo *philo);
void	sleep_think(t_philo *philo);
void	*check_if_alive(void *v_philos);
int		print_action(t_philo *philo, int sort);

#endif
