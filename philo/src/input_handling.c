/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:43:06 by demacinema        #+#    #+#             */
/*   Updated: 2024/07/12 01:12:00 by demacinema       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* CHECK IF DIGITS AND RANGE */
bool	check_input(char **argv)
{
	int	i;
	int	k;

	i = 0;
	k = 1;
	while (argv[k])
	{
		while (argv[k][i])
		{
			if (!(argv[k][i] >= '0' && argv[k][i] <= '9'))
			{
				printf("ONLY DIGITS!%i\n", argv[k][i]);
				return (false);
			}
			i++;
		}
		if (ft_atol(argv[k]) <= 0)
			return (printf("BETWEEN 0 AND 100000000!\n"), false);
		i = 0;
		k++;
	}
	return (true);
}
/* CREATE MUTEX FOR EVERY PHILO */
void	create_data_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philos + 1);
	while (i < data->nbr_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->alive_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

/* INITIALISE PHILO STRUCT */
void	init_philo_structs(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nbr_philos + 1);
	while (i < data->nbr_philos)
	{
		data->philo[i].meals_eaten = 0;
		data->philo[i].id = i;
		if (i + 1 == data->nbr_philos)
			data->philo[i].next_id = 0;
		else
			data->philo[i].next_id = i + 1;
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].last_meal_mutex, NULL);
		pthread_mutex_init(&data->philo[i].meals_eaten_mutex, NULL);
		i++;
	}
}

/* PUT ARGS IN DATA STRUCT */
void	initalise_arguments(char **argv, t_data	*data)
{
	data->nbr_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->all_alive = true;
	data->print_lock = false;
	if (argv[5])
		data->nbr_meals = ft_atol(argv[5]);
	else
		data->nbr_meals = -1;
}
