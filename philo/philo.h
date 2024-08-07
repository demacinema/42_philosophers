/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:49:42 by demacinema        #+#    #+#             */
/*   Updated: 2024/07/12 01:22:33 by demacinema       ###   ########.fr       */
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

# define D "\e[38;5;198m"
# define RED "\e[38;5;203m"
# define GREEN "\e[38;5;84m"
# define BLUE "\e[38;5;104m"
# define ORANGE "\e[38;5;220m"

# define EAT " EATING!!!\e[0m\n"
# define THINK " THINKING!!!\e[0m\n"
# define SLEEP " START SLEEP!!!\e[0m\n"
# define FORK " GET FORK!!! \e[0m\n"
# define DIE " DIED!!!\e[0m\n"

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

void		final_free(t_data	*data);
void		one_philo_routine(t_data *data);

bool		check_input(char **argv);
void		initalise_arguments(char **argv, t_data	*data);

long		ft_atol(const char *str);
long		number_convert(int x, long nbr, const char *str);

void		print_data(t_data *data);
void		test_wait(t_data *data);

void		ft_sleep(long time_to_wait);
long long	get_curr_time(void);

void		*philo_process(void *philo_arg);
void		create_data_mutex(t_data *data);
void		start_philo_threads(t_data *data);
void		trying_to_eat(t_philo *philo, t_data *data);

bool		grab_my_fork(t_philo *philo, t_data *data);
bool		grab_next_fork(t_philo *philo, t_data *data);
void		drop_forks(t_philo *philo, t_data *data);
void		drop_my_fork(t_philo *philo, t_data *data);
void		drop_next_philo_fork(t_philo *philo, t_data *data);

void		print_status(char *color, char *action, t_data *data, t_philo *philo);

void		*status_process(void *data_arg);
bool		status_process_loop(t_data *data, int i);
void		*meal_check(void *data_arg);
bool		meal_process(t_data *data);
void		init_philo_structs(t_data *data);

#endif