
#include "../philo.h"

void	start_philo_threads(t_data *data)
{
	int			i;
	pthread_t	doctor;
	pthread_t	meal_checker;

	i = 0;
	data->start_time = get_curr_time();
	while (i < data->philo_amount)
	{
		if (pthread_create(&data->philo[i].th, NULL, &routine, &data->philo[i]))
			return (perror("thread create fail"));
		i++;
	}
	pthread_create(&doctor, NULL, &doc_routine, data);
	if (data->meal_amount != -1)
		pthread_create(&meal_checker, NULL, &meal_check, data);
	i = 0;
	while (i < data->philo_amount)
	{
		pthread_join(data->philo[i].th, NULL);
		i++;
	}
	pthread_join(doctor, NULL);
	if (data->meal_amount != -1)
		pthread_join(meal_checker, NULL);
}

void	*routine(void *philo_arg)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	data = philo->data;
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_curr_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if ((philo->id + 1) % 2 == 0)
		ft_isleep(data->time_to_eat / 2);
	pthread_mutex_lock(&data->alive_mutex);
	while (data->all_alive == true)
	{
		pthread_mutex_unlock(&data->alive_mutex);
		trying_to_eat(philo, data);
		printer(BLUE, SLEEP, data, philo);
		ft_isleep(data->time_to_sleep);
		printer(ORANGE, THINK, data, philo);
		pthread_mutex_lock(&data->alive_mutex);
	}
	pthread_mutex_unlock(&data->alive_mutex);
	return (NULL);
}

void	trying_to_eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->id]);
	printer(GREEN, FORK, data, philo);
	pthread_mutex_lock(&data->forks[philo->next_id]);
	printer(GREEN, FORK, data, philo);
	printer(RED, EAT, data, philo);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_curr_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ft_isleep(data->time_to_eat);
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	pthread_mutex_unlock(&data->forks[philo->id]);
	pthread_mutex_unlock(&data->forks[philo->next_id]);
}

void	printer(char *color, char *action, t_data *data, t_philo *philo)
{
	long	t;

	t = 0;
	pthread_mutex_lock(&data->print_mutex);
	if (data->print_protection == false)
	{
		t = get_curr_time() - data->start_time;
		printf("%s%ldms philo %d%s", color, t, philo->id + 1, action);
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&data->print_mutex);
}
