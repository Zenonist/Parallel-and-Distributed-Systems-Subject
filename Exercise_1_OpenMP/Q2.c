/*
Write an OpenMP program to find the summation of values in A[] using reduction
clause (+ operator).
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
    int array[100];
    srand(1234);
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i=0; i<100; i++){
        array[i] = rand()%1000;
        sum = sum + array[i];
    }
    printf("%d\n",sum);
    return 0;
}