/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:37:31 by demrodri          #+#    #+#             */
/*   Updated: 2024/06/26 17:53:06 by demrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <pthread.h>
#include <stdio.h>

// Thread function to generate output
void *threadFunc(void *arg) {
    char *str = (char *)arg;
    printf("%s\n", str);
    return NULL;
}

int main() {
    pthread_t tid;
    char *message = "Hello, World from thread!";
    
    // Create a new thread that will execute 'threadFunc'
    if (pthread_create(&tid, NULL, threadFunc, message)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    
    // Wait for the created thread to terminate
    if (pthread_join(tid, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    
    return 0;
}

// A thread is a sequence of instructions that can be executed independently of other code.
// Think of a program as a book. A single-threaded program is like reading the book from start to finish in a straight line.
// A multi-threaded program, on the other hand, is like having multiple readers reading different chapters of the book at the same time.
// Each reader (thread) can read (execute) different parts of the book (program) simultaneously, making the overall process faster and more efficient.

// Threads are a way for a program to do multiple things at once.

// For example, in a web browser, one thread might display images on the screen while another thread downloads data from the internet.
// They share the same memory space, so they can access the same data and communicate with each other more easily than separate processes (which are like separate programs running on the computer).

// In summary, a thread is a path of execution within a program that can run concurrently with other threads, allowing the program to perform multiple operations at the same time.