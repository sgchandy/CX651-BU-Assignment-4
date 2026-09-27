#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"
#include "scheduler.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <FIFO/SJF> <job_sizes_comma_separated> \n", argv[0]);
        return 1;
    }
    
    char *scheduler_type = argv[1];
    char *job_sizes_str = argv[2];

    // Split the job_sizes_str by commas and convert to integers
    // Count the number of jobs by counting commas and adding 1
    int num_jobs = 1;
    for (char *p = job_sizes_str; *p; p++) {
        if (*p == ',') num_jobs++;
    }

    // Allocate memory for the jobs array based on the number of jobs
    int *jobs = malloc(num_jobs * sizeof(int));
    if (!jobs) {
        perror("malloc");
        return 1;
    }

    // Tokenize the job_sizes_str and fill the jobs array
    char *token = strtok(job_sizes_str, ",");
    // Start tokenizing the string
    for (int i = 0; i < num_jobs; i++) {
        // Check if the token is NULL before converting it to an integer
        if (!token) {
            fprintf(stderr, "Error parsing job sizes\n");
            free(jobs);
            return 1;
        }
        // Convert the token to an integer and store it in the jobs array
        jobs[i] = atoi(token);
        // Move to the next token
        token = strtok(NULL, ",");
    }

    float result;
    if (strcmp(scheduler_type, "FIFO") == 0) {
        result = FIFO(jobs, num_jobs);
    } else if (strcmp(scheduler_type, "SJF") == 0) {
        result = SJF(jobs, num_jobs);
    } else {
        fprintf(stderr, "Unknown scheduler type: %s\n", scheduler_type);
        free(jobs);
        return 1;
    }

    printf("Average turnaround time: %.2f\n", result);
    free(jobs);

    return 0;
}