/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 02:01:23 by nsimon            #+#    #+#             */
/*   Updated: 2021/07/30 09:18:17 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->status->m_print);
	if (philo->status->good == 1)
	{
		printf("%lld %d %s\n", get_time() - philo->status->time,
			philo->id + 1, str);
	}
	pthread_mutex_unlock(&philo->status->m_print);
}

void	find_forks(t_main *status, int id)
{
	status->philos[id].l_fork = &status->forks[id];
	if (id + 1 >= status->nbr_philo)
		status->philos[id].r_fork = &status->forks[0];
	else
		status->philos[id].r_fork = &status->forks[id + 1];
}

void	start_half(t_main *status, int i)
{
	while (i < status->nbr_philo)
	{
		status->philos[i].status = status;
		status->philos[i].id = i;
		status->philos[i].last_eat = status->time;
		status->philos[i].limit_eat = status->time + status->timeToDie;
		status->philos[i].nbr_eat = 0;
		find_forks(status, i);
		pthread_mutex_init(&status->philos[i].m_eating, NULL);
		pthread_create(&status->philos[i].thread, NULL, philosopher,
			&status->philos[i]);
		i += 2;
	}
}

void	philo_eat(t_philo *philo)
{
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
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (philo->status->nbrEat != -1)
	{
		pthread_mutex_lock(&philo->status->m_eat_count);
		philo->nbr_eat++;
		philo->status->eat_count++;
		pthread_mutex_unlock(&philo->status->m_eat_count);
	}
}
