/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passing_data_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:57:01 by demrodri          #+#    #+#             */
/*   Updated: 2024/06/26 17:58:36 by demrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Passing data between threads in C can be done using shared memory, since threads in the same process share the same memory space.
// Here's a step-by-step approach to passing data between threads:

// 1.Define a Struct for Shared Data: Create a struct that contains the data you want to share between threads.
// 2.Allocate Memory for Shared Data: Dynamically allocate memory for the shared data structure to ensure it remains valid throughout the thread's lifetime.
// 3.Initialize the Shared Data: Before creating threads, initialize the shared data structure with the necessary values.
// 4.Pass the Shared Data to Threads: When creating threads with pthread_create, pass a pointer to the shared data structure as the argument.
// 5.Use the Shared Data in Threads: Inside the thread function, cast the void* argument back to the original data structure type and access the shared data.
// 6.Clean Up: After all threads have finished using the shared data, ensure to free the dynamically allocated memory to avoid memory leaks.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Define a struct for shared data
typedef struct {
    int value;
    // Add more shared data here
} SharedData;

// Thread function that uses the shared data
void* threadFunction(void* arg) {
    SharedData* sharedData = (SharedData*)arg;
    printf("Thread sees value: %d\n", sharedData->value);
    // Modify the shared data if necessary
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    SharedData* sharedData = malloc(sizeof(SharedData)); // Allocate memory for shared data

    // Initialize shared data
    sharedData->value = 42;

    // Create threads, passing the shared data as an argument
    pthread_create(&thread1, NULL, threadFunction, (void*)sharedData);
    pthread_create(&thread2, NULL, threadFunction, (void*)sharedData);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Clean up
    free(sharedData); // Free the allocated memory for shared data

    return 0;
}

// In this example, both threads receive a pointer to the same SharedData instance.
// They print the value stored in this shared structure, demonstrating how data can be passed to and shared between threads.
// Remember, when sharing data between threads, it's crucial to consider thread safety, especially when threads modify shared data.
// For such cases, using mutexes or other synchronization mechanisms is necessary to prevent data races and ensure data integrity.