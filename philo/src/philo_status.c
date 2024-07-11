/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:47:45 by demacinema        #+#    #+#             */
/*   Updated: 2024/07/12 01:17:49 by demacinema       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* CHECK STATUS OF PHILOSOPHERS */
void	*status_process(void *data_arg)
{
	t_data	*data;

	data = (t_data *)data_arg;
	ft_sleep(data->time_to_die / 2);
	while (1)
	{
		if (status_process_loop(data, 0) == false)
			return (NULL);
		usleep(50);
	}
	return (NULL);
}

/* CHECK IF PHILOSOPHER IS DEAD */
bool	status_process_loop(t_data *data, int i)
{
	unsigned long long	time;

	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->philo[i].last_meal_mutex);
		if (get_curr_time() - data->philo[i].last_meal > data->time_to_die)
		{
			pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
			pthread_mutex_lock(&data->print_mutex);
			if (data->print_lock != true)
			{
				time = get_curr_time() - data->start_time;
				printf("%s%llums philo %d%s", D, time, data->philo[i].id + 1, DIE);
			}
			data->print_lock = true;
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_lock(&data->alive_mutex);
			data->all_alive = false;
			pthread_mutex_unlock(&data->alive_mutex);
			return (false);
		}
		pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
		i++;
	}
	return (true);
}

/* CHECK IF PHILOSOPHER EATS A MEAL */
void	*meal_check(void *data_arg)
{
	t_data	*data;

	data = (t_data *)data_arg;
	pthread_mutex_lock(&data->alive_mutex);
	while (data->all_alive == true)
	{
		pthread_mutex_unlock(&data->alive_mutex);
		if (meal_process(data) == true)
			return (NULL);
		pthread_mutex_lock(&data->alive_mutex);
	}
	pthread_mutex_unlock(&data->alive_mutex);
	return (NULL);
}

/* CHECK IF ALL PHILOSOPHERS EAT A MEAL */
bool	meal_process(t_data *data)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->philo[i].meals_eaten_mutex);
		if (data->philo[i].meals_eaten >= data->nbr_meals)
			counter++;
		pthread_mutex_unlock(&data->philo[i].meals_eaten_mutex);
		i++;
	}
	if (counter == data->nbr_philos)
	{
		pthread_mutex_lock(&data->print_mutex);
		if (data->print_lock == false)
			printf("\e[38;5;14mAll meals are eaten!\e[0m\n");
		data->print_lock = true;
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_lock(&data->alive_mutex);
		data->all_alive = false;
		return (pthread_mutex_unlock(&data->alive_mutex), true);
	}
	return (false);
}
