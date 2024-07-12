/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:49:42 by demacinema        #+#    #+#             */
/*   Updated: 2024/07/12 03:29:19 by demrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>

# define ROSE "\e[38;5;198m"
# define RED "\e[38;5;203m"
# define GREEN "\e[38;5;84m"
# define BLUE "\e[38;5;104m"
# define ORANGE "\e[38;5;220m"
# define YELLOW "\e[38;5;226m"
# define PURPLE "\e[38;5;93m"
# define CYAN "\e[38;5;51m"
# define MAGENTA "\e[38;5;201m"
# define LIME "\e[38;5;118m"
# define PINK "\e[38;5;219m"
# define TEAL "\e[38;5;49m"
# define BROWN "\e[38;5;130m"
# define GREY "\e[38;5;245m"
# define BLACK "\e[38;5;0m"
# define WHITE "\e[38;5;255m"

# define EAT " EATING\e[0m\n"
# define THINK " THINKING\e[0m\n"
# define SLEEP " SLEEPING\e[0m\n"
# define FORK " FORKING \e[0m\n"
# define DIE " DEAD\e[0m\n"

/* 1.NBR_PHILOSOPHERS
 * 2.TIME_TO_DIE
 * 3.TIME_TO_EAT
 * 4.TIME_TO_SLEEP
 * 5.(OPT)NBR_MEALS */

struct	s_philo;

typedef struct s_data
{
	long long		start_time;
	long			nbr_philos;
	long long		time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_meals;
	pthread_mutex_t	*forks;
	struct s_philo	*philo;
	pthread_mutex_t	alive_mutex;
	bool			all_alive;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	start_mutex;
	bool			print_lock;
}				t_data;

typedef struct s_philo
{
	int					id;
	int					next_id;
	pthread_t			thread;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		meals_eaten_mutex;
	long				last_meal;
	t_data				*data;
	int					meals_eaten;
}				t_philo;

//input_handling.c
bool		check_input(char **argv);
void		create_data_mutex(t_data *data);
void		init_philo_structs(t_data *data);
void		initalise_arguments(char **argv, t_data	*data);

//main.c
void		one_philo_process(t_data *data);
void		final_free(t_data	*data);

//philo_status.c
void		*status_process(void *data_arg);
bool		status_process_loop(t_data *data, int i);
void		*meal_check(void *data_arg);
bool		meal_process(t_data *data);

//philo_utils_1.c
void		start_philo_threads(t_data *data);
void		*philo_process(void *philo_arg);
void		trying_to_eat(t_philo *philo, t_data *data);
void		print_status(char *color, char *action, \
			t_data *data, t_philo *philo);

//philo_utils_2.c
void		ft_sleep(long time_to_wait);
long long	get_curr_time(void);
long		number_convert(int x, long nbr, const char *str);
long		ft_atol(const char *str);

#endif