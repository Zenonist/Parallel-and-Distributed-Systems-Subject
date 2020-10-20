#include <stdio.h>
#define N 1314
#define T 256

__global__ void vecMult(int *A ,int *B){
    int i = 0;
    for (i = threadIdx.x; i < N;i = i + T)
        B[i] = A[i] * 2;
}
int main (int argc, char *argv[]){
    int i = 0;
    int size = N * sizeof (int);
    int a[N], b[N], *devA, *devB;
    for (i = 0; i < N; i++){
        a[i] = i;
    }
    cudaMalloc( (void**)&devA,size);
    cudaMalloc( (void**)&devB,size);
    
    cudaMemcpy( devA, a, size, cudaMemcpyHostToDevice);
    
    vecMult<<<1,T>>>(devA,devB);
    
    cudaMemcpy( b, devB, size, cudaMemcpyDeviceToHost);
    cudaFree(devA);
    cudaFree(devB);
    for (i = 0;i < N; i++){
        printf("%d ",b[i]);
    }
    printf("\n");
}