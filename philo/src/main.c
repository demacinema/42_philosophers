/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:03:59 by demacinema        #+#    #+#             */
/*   Updated: 2024/07/12 01:20:22 by demacinema       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* 1.NBR_PHILOSOPHERS
 * 2.TIME_TO_DIE
 * 3.TIME_TO_EAT
 * 4.TIME_TO_SLEEP
 * 5.(OPT)NBR_MEALS */
int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (printf("WRONG NUMBER OF ARGUMENTS\n"), 1);
	if (!check_input(argv))
		return (1);
	data = malloc(sizeof(t_data));
	initalise_arguments(argv, data);
	if (data->nbr_meals == 0)
		return (free(data), printf("NO MEALS!! :(\n"), 0);
	if (data->nbr_philos == 1)
		return (one_philo_routine(data), 0);
	create_data_mutex(data);
	init_philo_structs(data);
	start_philo_threads(data);
	final_free(data);
	return (0);
}

void	one_philo_routine(t_data *data)
{
	printf("%s%dms philo %d%s", ORANGE, 0, 1, FORK);
	ft_sleep(data->time_to_die);
	printf("%s%llums philo %d%s", D, data->time_to_die + 1, 1, DIE);
	free(data);
}

void	final_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_destroy(&data->philo[i].last_meal_mutex);
		pthread_mutex_destroy(&data->philo[i].meals_eaten_mutex);
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			printf("mutex destroy error\n");
		i++;
	}
	free(data->forks);
	free(data->philo);
	pthread_mutex_destroy(&data->alive_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free (data);
}
