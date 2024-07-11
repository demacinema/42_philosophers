/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:13:31 by demacinema        #+#    #+#             */
/*   Updated: 2024/07/12 01:19:08 by demacinema       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* START PHILO THREADS */
void	start_philo_threads(t_data *data)
{
	int			i;
	pthread_t	doctor;
	pthread_t	meal_checker;

	i = 0;
	data->start_time = get_curr_time();
	while (i < data->nbr_philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &philo_process, &data->philo[i]))
			return (perror("thread create fail"));
		i++;
	}
	pthread_create(&doctor, NULL, &status_process, data);
	if (data->nbr_meals != -1)
		pthread_create(&meal_checker, NULL, &meal_check, data);
	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(doctor, NULL);
	if (data->nbr_meals != -1)
		pthread_join(meal_checker, NULL);
}

/* PHILO PROCESS */
void	*philo_process(void *philo_arg)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	data = philo->data;
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_curr_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if ((philo->id + 1) % 2 == 0)
		ft_sleep(data->time_to_eat / 2);
	pthread_mutex_lock(&data->alive_mutex);
	while (data->all_alive == true)
	{
		pthread_mutex_unlock(&data->alive_mutex);
		trying_to_eat(philo, data);
		print_status(BLUE, SLEEP, data, philo);
		ft_sleep(data->time_to_sleep);
		print_status(ORANGE, THINK, data, philo);
		pthread_mutex_lock(&data->alive_mutex);
	}
	pthread_mutex_unlock(&data->alive_mutex);
	return (NULL);
}

/* GET READY TO EAT */
void	trying_to_eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->id]);
	print_status(GREEN, FORK, data, philo);
	pthread_mutex_lock(&data->forks[philo->next_id]);
	print_status(GREEN, FORK, data, philo);
	print_status(RED, EAT, data, philo);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_curr_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ft_sleep(data->time_to_eat);
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	pthread_mutex_unlock(&data->forks[philo->id]);
	pthread_mutex_unlock(&data->forks[philo->next_id]);
}

/* PRINT STATUS */
void	print_status(char *color, char *action, t_data *data, t_philo *philo)
{
	long	time;

	time = 0;
	pthread_mutex_lock(&data->print_mutex);
	if (data->print_lock == false)
	{
		time = get_curr_time() - data->start_time;
		printf("%s%ldms philo %d%s", color, time, philo->id + 1, action);
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&data->print_mutex);
}
