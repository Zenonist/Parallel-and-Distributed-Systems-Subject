#include <stdio.h>
#include <stdlib.h>
#define N 1000
#define T 256
__global__ void vecInc(int *A,int *newA){
    int i;
    for (i = threadIdx.x;i < N;i = i + T){
	newA[i] = A[i] + 1;
    }
}
int main (int argc, char *argv[]){
    int i;
    int size = N * sizeof ( int);
    int a[N], new_a[N], *devA, *dev_newA;
    printf("Original A array\n");
    for (i = 0; i < N; i++){
        a[i] = rand() % 100;
	printf("%d ",a[i]);
    }
    cudaMalloc( (void**)&devA, size);
    cudaMalloc( (void**)&dev_newA, size);

    cudaMemcpy( devA, a, size, cudaMemcpyHostToDevice);

    vecInc<<<1, T>>>(devA, dev_newA);
    cudaMemcpy( new_a, dev_newA, size, cudaMemcpyDeviceToHost);
    cudaFree( devA);
    cudaFree( dev_newA);
    printf("\nNew A array \n");
    for (i= 0; i < N; i++){
        printf("%d ",new_a[i]);
    }
    printf("\n");
}