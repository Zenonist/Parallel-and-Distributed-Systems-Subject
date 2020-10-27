#include <stdio.h>
#define N 100
#define T 20

__global__ void MatrixIncrement (int *a){
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    int index = y * N + x;
    a[index] = a[index] + 1;
}

int main(int argc, char *argv[]){
    int size = N * N * sizeof(int);
    int a[N][N] , *devA;
    srand(1234);
    
    printf("Original A array\n");
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            a[i][j] = rand() % 1000;
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    
    cudaMalloc((void**)&devA, size);
    
    cudaMemcpy(devA, a, size, cudaMemcpyHostToDevice);
    
    dim3 dimBlock(T,T);
    dim3 dimGrid(N/dimBlock.x,N/dimBlock.y);
    
    MatrixIncrement<<<dimGrid,dimBlock>>>(devA);
    
    cudaMemcpy(a, devA, size, cudaMemcpyDeviceToHost);
    
    cudaFree(devA);
    
    printf("\nNew A array \n");
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}