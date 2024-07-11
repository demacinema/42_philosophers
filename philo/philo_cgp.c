/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cgp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:32:37 by demrodri          #+#    #+#             */
/*   Updated: 2024/06/26 18:32:40 by demrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];

void* philosopher(void* num) {
    int id = *(int*)num;

    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    // To avoid deadlock, the last philosopher picks up the right chopstick first
    if (id == NUM_PHILOSOPHERS - 1) {
        int temp = left;
        left = right;
        right = temp;
    }

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1); // Simulate thinking

        pthread_mutex_lock(&chopsticks[left]);
        printf("Philosopher %d picked up left chopstick.\n", id);
        pthread_mutex_lock(&chopsticks[right]);
        printf("Philosopher %d picked up right chopstick and starts eating.\n", id);

        sleep(1); // Simulate eating

        pthread_mutex_unlock(&chopsticks[right]);
        printf("Philosopher %d put down right chopstick.\n", id);
        pthread_mutex_unlock(&chopsticks[left]);
        printf("Philosopher %d put down left chopstick.\n", id);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_numbers[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_numbers[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_numbers[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}