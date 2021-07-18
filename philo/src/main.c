/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:21:31 by nsimon            #+#    #+#             */
/*   Updated: 2021/07/18 21:00:01 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!philo->status->good)
			return (NULL);
		pthread_mutex_lock(philo->l_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->m_eating);
		print_message(philo, "is eating");
		philo->last_eat = get_time();
		philo->limit_eat = philo->last_eat + philo->status->timeToDie;
		pthread_mutex_unlock(&philo->m_eating);
		ft_usleep(philo->status, philo->status->timeToEat);
		if (!philo->status->good)
			return (NULL);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		print_message(philo, "is sleeping");
		ft_usleep(philo->status, philo->status->timeToSleep);
		if (!philo->status->good)
			return (NULL);
		print_message(philo, "is thinking");
	}
}

void	*monitor(void *arg)
{
	t_main		*status;
	int			i;

	status = (t_main *)arg;
	while (1)
	{
		i = -1;
		while (++i < status->nbr_philo)
		{
			pthread_mutex_lock(&status->philos[i].m_eating);
			if (get_time() > status->philos[i].limit_eat)
			{
				pthread_mutex_lock(&status->m_good);
				status->good = 0;
				pthread_mutex_unlock(&status->m_good);
				pthread_mutex_lock(&status->m_print);
				printf("%lld %d is dead\n", get_time() - status->time, i + 1);
				pthread_mutex_unlock(&status->m_print);
				return (NULL);
			}
			pthread_mutex_unlock(&status->philos[i].m_eating);
		}
		usleep(100);
	}
}

int	create_philo(t_main *status)
{
	int	i;

	status->time = get_time();
	status->philos = malloc(sizeof(t_philo) * status->nbr_philo);
	status->forks = malloc(sizeof(pthread_mutex_t) * status->nbr_philo);
	pthread_mutex_init(&status->m_print, NULL);
	i = -1;
	while (++i < status->nbr_philo)
		pthread_mutex_init(&status->forks[i], NULL);
	pthread_mutex_init(&status->m_good, NULL);
	start_half(status, 0);
	ft_usleep(status, 10);
	start_half(status, 1);
	pthread_create(&status->monitor, NULL, monitor, status);
	pthread_join(status->monitor, NULL);
	i = -1;
	while (++i < status->nbr_philo)
		pthread_detach(status->philos[i].thread);
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
		status.good = 1;
		create_philo(&status);
	}
	return (0);
}
