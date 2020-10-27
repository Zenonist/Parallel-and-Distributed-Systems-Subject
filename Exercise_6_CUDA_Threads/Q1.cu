#include <stdio.h>

#define N 1250
#define T 250

__global__ void vecAssign(int *a){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N){
        a[i] = i * 2;
    }
}

int main(int argc, char *argv[]){
    int size = N * sizeof(int);
    int a[N], *devA;
    int blocks;
    //Compute the blocks in case that N % T != 0
    if (N % T != 0){
        blocks =(N+T-1) / T;
    }else{
        blocks = N/T;
    }
    
    cudaMalloc( (void**)&devA, size);
    
    cudaMemcpy(devA, a, size, cudaMemcpyHostToDevice);
    
    vecAssign<<<blocks,T>>>(devA);
    
    cudaMemcpy(a, devA, size, cudaMemcpyDeviceToHost);
    
    cudaFree(devA);
    
    for (int i = 0; i < N; i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}