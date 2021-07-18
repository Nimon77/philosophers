/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 02:01:23 by nsimon            #+#    #+#             */
/*   Updated: 2021/07/18 16:48:35 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->status->m_print);
	printf("%ld %d %s\n", get_time() - philo->status->time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->status->m_print);
}

void	find_forks(t_main *status, int id)
{
	status->philos[id].l_fork = &status->forks[id];
	if (id + 1 > status->nbr_philo)
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
		find_forks(status, i);
		pthread_mutex_init(&status->philos[i].m_eating, NULL);
		pthread_create(&status->philos[i].thread, NULL, philosopher,
			&status->philos[i]);
		i += 2;
	}
}
