/* 
Given an integer array A[100], write an OpenMP program that multiplies 10 to each
element of the array.
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
    int array[100];
    srand(1234);
    #pragma omp parallel for
    for (int i=0; i<100; i++){
        array[i] = rand()%1000;
        array[i] = array[i] * 10;
        printf("%d\n",array[i]);
    }
    return 0;
}