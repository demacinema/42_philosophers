
#include "../philo.h"

void	*doc_routine(void *data_arg)
{
	t_data	*data;

	data = (t_data *)data_arg;
	ft_isleep(data->time_to_die / 2);
	while (1)
	{
		if (doc_routine_loop(data, 0) == false)
			return (NULL);
		usleep(50);
	}
	return (NULL);
}

bool	doc_routine_loop(t_data *data, int i)
{
	unsigned long long	t;

	while (i < data->philo_amount)
	{
		pthread_mutex_lock(&data->philo[i].last_meal_mutex);
		if (get_curr_time() - data->philo[i].last_meal > data->time_to_die)
		{
			pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
			pthread_mutex_lock(&data->print_mutex);
			if (data->print_protection != true)
			{
				t = get_curr_time() - data->start_time;
				printf("%s%llums philo %d%s", D, t, data->philo[i].id + 1, DIE);
			}
			data->print_protection = true;
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

void	*meal_check(void *data_arg)
{
	t_data	*data;

	data = (t_data *)data_arg;
	pthread_mutex_lock(&data->alive_mutex);
	while (data->all_alive == true)
	{
		pthread_mutex_unlock(&data->alive_mutex);
		if (meal_check_routine(data) == true)
			return (NULL);
		pthread_mutex_lock(&data->alive_mutex);
	}
	pthread_mutex_unlock(&data->alive_mutex);
	return (NULL);
}

bool	meal_check_routine(t_data *data)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (i < data->philo_amount)
	{
		pthread_mutex_lock(&data->philo[i].meals_eaten_mutex);
		if (data->philo[i].meals_eaten >= data->meal_amount)
			counter++;
		pthread_mutex_unlock(&data->philo[i].meals_eaten_mutex);
		i++;
	}
	if (counter == data->philo_amount)
	{
		pthread_mutex_lock(&data->print_mutex);
		if (data->print_protection == false)
			printf("\e[38;5;14mAll meals are eaten!\e[0m\n");
		data->print_protection = true;
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_lock(&data->alive_mutex);
		data->all_alive = false;
		return (pthread_mutex_unlock(&data->alive_mutex), true);
	}
	return (false);
}
