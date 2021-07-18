/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:21:47 by nsimon            #+#    #+#             */
/*   Updated: 2021/07/18 16:43:16 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	time_t			last_eat;
	pthread_mutex_t	m_eating;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_main	*status;
}	t_philo;

typedef struct s_main
{
	int				nbr_philo;
	int				timeToDie;
	int				timeToEat;
	int				timeToSleep;
	int				good;
	pthread_mutex_t	m_good;
	time_t			time;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_dead;
}	t_main;

typedef struct s_args
{
	t_main	*status;
	t_philo	*philo;
}	t_args;

int			ft_strlen(const char *str);
int			ft_atoi(const char *str);
time_t		get_time(void);
void		*philosopher(void *arg);
void		start_half(t_main *status, int i);
void		ft_usleep(t_main *status, int stop_ms);
void		ft_putnbr_fd(int n, int fd);
void		print_message(t_philo *philo, char *str);

#endif
