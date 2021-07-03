/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:21:04 by nsimon            #+#    #+#             */
/*   Updated: 2021/07/04 00:11:17 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return i;
}

int			ft_atoi(const char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i] != '\0')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

void		ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	tmp[12];

	i = 0;
	while (n != 0)
	{
		if ((tmp[i] = (n % 10)) < 0)
			tmp[i] = -tmp[i] + '0';
		else
			tmp[i] += '0';
		i++;
		if (n / 10 == 0 && n < 0)
			tmp[i++] = '-';
		n /= 10;
	}
	if (i == 0)
		tmp[i++] = '0';
	tmp[i] = '\0';
	while (i != 0)
		write(fd, &tmp[--i], 1);
}

time_t		get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(t_main *status, int stop_ms)
{
	time_t	end_ms;

	end_ms = get_time() + stop_ms;
	while (get_time() < end_ms)
	{
//		printf("%ld\t%ld\n", get_time(), end_ms);
		if (status->dead == 1)
			return ;
		usleep(100);
	}
}
