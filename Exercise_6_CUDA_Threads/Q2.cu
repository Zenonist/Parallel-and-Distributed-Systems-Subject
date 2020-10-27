#include <stdio.h>

#define N 2250
#define T 512

__global__ void vecReverse(int *a, int *b){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N){
        b[i] = a[N - i - 1];
    }
}

int main(int argc, char *argv[]){
    int size = N * sizeof(int);
    int a[N], b[N], *devA, *devB;
    int blocks;
    if (N % T != 0){
        blocks =(N+T-1) / T;
    }else{
        blocks = N/T;
    }
    
    for (int i = 0; i < N; i++){
        a[i] = i;
    }
    
    cudaMalloc((void**)&devA, size);
    cudaMalloc((void**)&devB, size);
    
    cudaMemcpy(devA, a, size, cudaMemcpyHostToDevice);
    
    vecReverse<<<blocks,T>>>(devA,devB);
    
    cudaMemcpy(b, devB, size, cudaMemcpyDeviceToHost);
    
    cudaFree(devA);
    cudaFree(devB);
    
    for (int i = 0; i < N; i++){
        printf("%d ",b[i]);
    }
    printf("\n");
}