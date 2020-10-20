/*
Write an OpenMP program to find the summation of values in A[] without using reduction
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
    int array[100];
    srand(1234);
    int psum = 0;
    int sum = 0;
    #pragma omp parallel private(psum) shared(sum) num_threads(4)
        for (int i = omp_get_thread_num() * (100/omp_get_num_threads()); i < (omp_get_thread_num() + 1)*(100/omp_get_num_threads()); i++){
            array[i] = rand() % 1000;
            psum = psum + array[i];
            if (i == (((omp_get_thread_num() + 1)*(100/omp_get_num_threads()))- 1)){
                sum = sum + psum;
            }
        }
        printf("%d\n", sum);
}