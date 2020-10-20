/*
Write an OpenMP program to find the maximum value in an integer array using
reduction clause (max operator).
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main (){
    int array[100];
    srand(1234);
    int maxi = 0;
    #pragma omp parallel for reduction(max : maxi)
    for (int i=0; i<100; i++){
        array[i] = rand()%1000;
        if (array[i] > maxi){
            maxi = array[i];
        }
    }
    printf("%d\n", maxi);
}