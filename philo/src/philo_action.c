/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 02:01:23 by nsimon            #+#    #+#             */
/*   Updated: 2021/07/04 00:20:55 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->status->print);
	ft_putnbr_fd((int)(get_time() - philo->status->time), 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->id + 1, 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&philo->status->print);
}
