
#include "../philo.h"

/* checks input for anything besides digits
   and if the number is in the range between 0 and max long */
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
				printf("Please put only digits as Params. %i\n", argv[k][i]);
				return (false);
			}
			i++;
		}
		if (ft_atol(argv[k]) <= 0)
			return (printf("Params has to between 0 and 100000000\n"), false);
		i = 0;
		k++;
	}
	return (true);
}

void	create_data_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_amount + 1);
	while (i < data->philo_amount)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->alive_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

void	init_philo_structs(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->philo_amount + 1);
	while (i < data->philo_amount)
	{
		data->philo[i].meals_eaten = 0;
		data->philo[i].id = i;
		if (i + 1 == data->philo_amount)
			data->philo[i].next_id = 0;
		else
			data->philo[i].next_id = i + 1;
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].last_meal_mutex, NULL);
		pthread_mutex_init(&data->philo[i].meals_eaten_mutex, NULL);
		i++;
	}
}

/*puts the argv arguments into the main data struct*/
void	initalise_arguments(char **argv, t_data	*data)
{
	data->philo_amount = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->all_alive = true;
	data->print_protection = false;
	if (argv[5])
		data->meal_amount = ft_atol(argv[5]);
	else
		data->meal_amount = -1;
}
