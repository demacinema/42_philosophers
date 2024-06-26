/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:38:02 by demrodri          #+#    #+#             */
/*   Updated: 2024/06/26 15:13:49 by demrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 6)
	{
		printf("Please insert the correct number of arguments:\n");
		printf("nbr_philos|time_to_die|time_to_eat|");
		printf("time_to_sleep|[nbr_philo_must_eat]\n");
	}
	else
	{
		printf("Call Philo function\n");
	}
	return (0);
}

// Your(s) program(s) should take the following arguments:
// number_of_philosophers / time_to_die / time_to_eat /
// time_to_sleep / [number_of_times_each_philosopher_must_eat]