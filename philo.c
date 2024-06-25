/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:36:59 by demrodri          #+#    #+#             */
/*   Updated: 2024/06/25 23:54:40 by demrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define N 5

void philosopher(int i)
{
    while (1)
    {
        think();//for some_time
        take_fork(r_fork[i]);
        
        if (available(l_fork[i]))
        {
            take_fork(l_fork[i]);
            eat();
        }
        
        take_fork(philo_left[i]);
        eat();
        put_fork(philo_left[i]);
        put_fork(philo_right[i]);        
    }
}