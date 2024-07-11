
#include "../philo.h"

/* 1. arg: Number of philos,
 * 2. arg: time philos have until they die,
 * 3. arg: time they need to eat,
 * 4. arg: time they need to sleep,
 * 5. arg: (optional) how many meals each eats until simulation stops; */
int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (printf("Wrong argument amount\n"), 1);
	if (!check_input(argv))
		return (1);
	data = malloc(sizeof(t_data));
	initalise_arguments(argv, data);
	if (data->meal_amount == 0)
		return (free(data), printf("No meals to be eaten :(\n"), 0);
	if (data->philo_amount == 1)
		return (one_philo_routine(data), 0);
	create_data_mutex(data);
	init_philo_structs(data);
	start_philo_threads(data);
	free_at_end(data);
	return (0);
}

void	one_philo_routine(t_data *data)
{
	printf("%s%dms philo %d%s", ORANGE, 0, 1, FORK);
	ft_isleep(data->time_to_die);
	printf("%s%llums philo %d%s", D, data->time_to_die + 1, 1, DIE);
	free(data);
}

void	free_at_end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_amount)
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
