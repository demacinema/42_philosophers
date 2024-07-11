/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:12:59 by demrodri          #+#    #+#             */
/*   Updated: 2024/06/26 23:39:30 by demrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// To handle synchronization between threads in C, especially when they access shared data, you can use mutexes (mutual exclusions). A mutex ensures that only one thread can access a resource, or execute a piece of code, at a time. This prevents "data races," where two or more threads read and write shared data concurrently, leading to unpredictable results.

// Here's how you can modify the example to include a mutex for synchronization:

// 1.Include the Mutex in the Shared Data Structure: Add a pthread_mutex_t field to your shared data structure.
// 2.Initialize the Mutex: Before creating threads, initialize the mutex using pthread_mutex_init.
// 3.Lock and Unlock the Mutex in Thread Functions: Before accessing shared data, lock the mutex using pthread_mutex_lock. After accessing the data, unlock it using pthread_mutex_unlock.
// 4.Destroy the Mutex: After all threads are done and joined, destroy the mutex using pthread_mutex_destroy.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int value;
    pthread_mutex_t mutex; // Mutex for synchronization
} SharedData;

void* threadFunction(void* arg) {
    SharedData* sharedData = (SharedData*)arg;
    
    // Lock the mutex before accessing shared data
    pthread_mutex_lock(&sharedData->mutex);
    printf("Thread sees value: %d\n", sharedData->value);
    // Optionally modify sharedData here
    pthread_mutex_unlock(&sharedData->mutex); // Unlock after access
    
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    SharedData* sharedData = malloc(sizeof(SharedData));

    sharedData->value = 42;
    pthread_mutex_init(&sharedData->mutex, NULL); // Initialize the mutex

    pthread_create(&thread1, NULL, threadFunction, (void*)sharedData);
    pthread_create(&thread2, NULL, threadFunction, (void*)sharedData);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&sharedData->mutex); // Destroy the mutex
    free(sharedData);

    return 0;
}