#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct timespec t0,t1;

void generate_random_matrix(int rows, int cols, int *matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = rand() % 100; // Random number between 0 and 9
        }
    }
}

void multiply_matrices(int rows1, int cols1, int *matrix1,
                       int rows2, int cols2, int *matrix2,
                       int *result) {

    //Resulting matrix result will have dimensions rows1 x cols2
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i * cols2 + j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i * cols2 + j] += matrix1[i * cols1 + k] * matrix2[k * cols2 + j];
            }
        }
    }
}

void display_matrix(int rows, int cols, int *matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i * cols + j]);
        }
        printf("\n");
    }   
}

float do_job(int rows1, int cols1, int cols2, int forever) {

    float total_time=0;
    do{
        timespec_get(&t0, TIME_UTC);
        int *matrix1 = (int *)malloc(rows1 * cols1 * sizeof(int));
        int *matrix2 = (int *)malloc(cols1 * cols2 * sizeof(int));
        printf("Generating Matrices...");
        generate_random_matrix(rows1, cols1, matrix1);
        printf("Matrix 1 done.\n");
        generate_random_matrix(cols1, cols2, matrix2);
        printf("Matrix 2 done.\n");
        int *result = (int *)malloc(rows1 * cols2 * sizeof(int));
        multiply_matrices(rows1, cols1, matrix1, cols1, cols2, matrix2, result);
        timespec_get(&t1, TIME_UTC);
        float dns = (float)(t1.tv_nsec - t0.tv_nsec)/1000000000;
        float ds = (float)(t1.tv_sec - t0.tv_sec);
        total_time = ds + dns;
        printf("%dx%d matrices: %f\n",rows1, cols2, total_time);
        free(result);
        free(matrix1);
        free(matrix2);
    }while(forever);
    
    return total_time;
}

