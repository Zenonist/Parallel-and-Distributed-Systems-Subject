#include <stdio.h>
#define N 578 // size of vectors
#define T 275 //number of threads per block
//Need to show array of a and b
__global__ void vecAdd(int *A ,int *B,int *C){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (i < N)
        C[i] = A[i] + B[i];
}

int main(int argc, char *argv[]){
    int blocks = (N + T - 1) / T;
    srand(1234);
    int i;
    int size = N * sizeof ( int);
    int a[N], b[N], c[N], *devA, *devB, *devC;
    for (i = 0;i < N; i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }
    cudaMalloc( (void**)&devA, size);
    cudaMalloc( (void**)&devB, size);
    cudaMalloc( (void**)&devC, size);
    
    cudaMemcpy( devA, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy( devB, b, size, cudaMemcpyHostToDevice);
    
    vecAdd<<<blocks,T>>>(devA,devB,devC);
    
    cudaMemcpy( c, devC, size, cudaMemcpyDeviceToHost);
    
    cudaFree( devA);
    cudaFree( devB);
    cudaFree( devC);
    
    for (i = 0; i < N; i++){
        printf("%d ",c[i]);
    }
    printf("\n");
}