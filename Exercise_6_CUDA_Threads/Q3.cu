#include <stdio.h>
#define N 2250
#define T 512

__global__ void vecReverse(int *a, int *b, int *c){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N){
        if (i % 2 == 0){
            c[i] = a[i] + b[i];
        }else{
            c[i] = a[i] - b[i];
        }
    }
}

int main(int argc, char *argv[]){
    int size = N * sizeof(int);
    int a[N], b[N], c[N], *devA, *devB, *devC;
    int blocks;
    if (N % T != 0){
        blocks =(N+T-1) / T;
    }else{
        blocks = N/T;
    }
        
    srand(1234);
    for (int i = 0; i < N; i++){
        a[i] = rand() % 1000;
        b[i] = rand() % 1000;
    }
    
    cudaMalloc((void**)&devA, size);
    cudaMalloc((void**)&devB, size);
    cudaMalloc((void**)&devC, size);
    
    cudaMemcpy(devA, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(devB, b, size, cudaMemcpyHostToDevice);
    
    vecReverse<<<blocks,T>>>(devA,devB,devC);
    
    cudaMemcpy(c, devC, size, cudaMemcpyDeviceToHost);
    
    cudaFree(devA);
    cudaFree(devB);
    cudaFree(devC);
    
    for (int i = 0; i < N; i++){
        printf("%d ",c[i]);
    }
    printf("\n");
}