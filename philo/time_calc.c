/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:50:26 by demrodri          #+#    #+#             */
/*   Updated: 2024/06/26 17:50:29 by demrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval start, end;
    long seconds, useconds;    
    double mtime;
    
    gettimeofday(&start, NULL); // Start time
    
    // Code block whose execution time you want to measure
    for (int i = 0; i < 1000000; i++) {
        // Some operations
    }
    
    gettimeofday(&end, NULL); // End time
    
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
    
    printf("Elapsed time: %f milliseconds\n", mtime);
    
    return 0;
}