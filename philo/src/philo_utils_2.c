/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:08:16 by demacinema        #+#    #+#             */
/*   Updated: 2024/07/12 01:11:14 by demacinema       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* WAIT FOR TIME IN MILLISECONDS */
void	ft_sleep(long time_to_wait)
{
	long long	wait_time;

	wait_time = get_curr_time() + time_to_wait;
	while (get_curr_time() <= wait_time)
		usleep(50);
}

/* GET CURRENT TIME IN MILLISECONDS */
long long	get_curr_time(void)
{
	struct timeval	time;
	long long		seconds;
	long long		microseconds;
	long long		milliseconds;

	gettimeofday(&time, NULL);
	seconds = time.tv_sec;
	microseconds = time.tv_usec;
	milliseconds = (microseconds / 1000) + (seconds * 1000);
	return (milliseconds);
}
/* CONVERT CHAR TO LONG */
long	number_convert(int x, long nbr, const char *str)
{
	long	res;

	res = 0;
	if (str[x] <= '9' && str[x] >= '0')
	{
		while (str[x] <= '9' && str[x] >= '0')
		{
			res *= 10;
			res += str[x] - '0';
			x++;
		}
		return (res * nbr);
	}
	else
		return (0);
}
/* CONVERT STRING TO LONG */
long	ft_atol(const char *str)
{
	long	x;
	long	nbr;

	nbr = 1;
	x = 0;
	while (str[x] == ' ' || str[x] == '\t' || str[x] == '\n' || str[x] == '\v'
		|| str[x] == '\f' || str[x] == '\r')
		x++;
	if (str[x] == '-' || str[x] == '+')
	{
		if (str[x] == '-')
			nbr *= -1;
		x++;
	}
	if (str)
		nbr = number_convert(x, nbr, str);
	return (nbr);
}
