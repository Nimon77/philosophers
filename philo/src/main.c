/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:21:31 by nsimon            #+#    #+#             */
/*   Updated: 2021/07/04 00:20:57 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_message(philo, " has taken a fork\n");
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, " has taken a fork\n");
	
		print_message(philo, " is eating\n");
		ft_usleep(philo->status, philo->status->timeToEat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);

		print_message(philo, " is sleeping\n");
		ft_usleep(philo->status, philo->status->timeToSleep);

		print_message(philo, " is thinking\n");
	}
}

void	find_forks(t_main *status, int id)
{
	status->philos[id].l_fork = &status->forks[id];
	if (id + 1 > status->nbr_philo)
		status->philos[id].r_fork = &status->forks[0];
	else
		status->philos[id].r_fork = &status->forks[id + 1];
}

int		create_philo(t_main *status)
{
	status->time = get_time();
	status->philos = malloc(sizeof(t_philo) * status->nbr_philo);
	status->forks = malloc(sizeof(pthread_mutex_t) * status->nbr_philo);
	pthread_mutex_init(&status->print, NULL);
	int i = 0;
	while (i < status->nbr_philo)
	{
		pthread_mutex_init(&status->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < status->nbr_philo)
	{
		status->philos[i].status = status;
		status->philos[i].id = i;
		find_forks(status, i);
		pthread_create(&status->philos[i].thread, NULL, philosopher, &status->philos[i]);
//		pthread_join(status->philos[i].thread, NULL);
		i += 2;
	}
	ft_usleep(status, 10);
	i = 1;
	while (i < status->nbr_philo)
	{
		status->philos[i].status = status;
		status->philos[i].id = i;
		find_forks(status, i);
		pthread_create(&status->philos[i].thread, NULL, philosopher, &status->philos[i]);
//		pthread_join(status->philos[i].thread, NULL);
		i += 2;
	}
	while (1) {}
	// pthread_create(status->philos, NULL, philosopher, status);
	// pthread_join(*status->philos, NULL);
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_main		status;

	if (argc > 4)
	{
		status.nbr_philo = ft_atoi(argv[1]);
		status.timeToDie = ft_atoi(argv[2]);
		status.timeToEat = ft_atoi(argv[3]);
		status.timeToSleep = ft_atoi(argv[4]);
		status.dead = 0;
		create_philo(&status);
	}
	return (0);
}
