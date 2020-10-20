/*
Write an OpenMP program to find the number of integers greater or equal to 500
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
    int array[100];
    srand(1234);
    #pragma omp parallel for
    for (int i=0; i<100; i++){
        array[i] = rand() % 1000;
        if (array[i] >= 500){
            printf("%d\n",array[i]);
        }
    }
}