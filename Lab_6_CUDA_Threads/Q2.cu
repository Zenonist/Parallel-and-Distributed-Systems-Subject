#include <stdio.h>
#define N 256 // size of vectors
#define T 64 //number of threads per block

__global__ void vecAdd(int *A){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (i < N)
        A[i] = i;
}

int main(int argc, char *argv[]){
    srand(1234);
    int i;
    int size = N * sizeof ( int);
    int a[N], *devA;
    cudaMalloc( (void**)&devA, size);
    
    cudaMemcpy( devA, a, size, cudaMemcpyHostToDevice);
    
    vecAdd<<<4,T>>>(devA);
    
    cudaMemcpy( a, devA, size, cudaMemcpyDeviceToHost);
    
    cudaFree( devA);
    
    for (i = 0; i < N; i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}