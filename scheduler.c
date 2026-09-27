#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"


float SJF(int* jobs, int size) {
    float total_time = 0;
    
    // Sort the jobs array in ascending order
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (jobs[i] > jobs[j]) {
                int temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }

    // After sorting, the jobs array is in ascending order, which is required for SJF
    for (int i = 0; i < size; i++){
        float result = do_job(jobs[i],jobs[i], jobs[i], 0 );
        total_time += result;
    }

    // Calculate and return the average time
    float average_time = total_time / size;

    printf("Total time for SJF: %.2f\n", total_time);
    printf("Average time for SJF: %.2f\n", average_time);

    return average_time;
}

float FIFO(int* jobs, int size) {
    float total_time = 0;
    
    //Processing jobs in order for FIFO
    for (int i = 0; i < size; i++) {
        float result = do_job(jobs[i], jobs[i], jobs[i], 0);
        total_time += result;
    }

    // Calculate the average time for FIFO
    float average_time = total_time / size;

    printf("Total time for FIFO: %.2f\n", total_time);
    printf("Average time for FIFO: %.2f\n", average_time);
    
    return average_time;
}
