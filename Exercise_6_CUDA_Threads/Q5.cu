#include <stdio.h>

#define Width 16
#define T 4

__global__ void vecTranspose(int *a, int *b, int width , int size) {
    int Row = blockIdx.y * blockDim.y + threadIdx.y;
    int Col = blockIdx.x * blockDim.x + threadIdx.x;
    for (int k = 0; k < width; k++){
        //int index = Row * width + Col;
        b[Row * width + k] = a[k * width + Col];
        //printf("%d %d\n",b[Row * width + k],a[k * width + Col]);
        //printf("%d %d %d %d\n",k * width + Col,Row * width + k,k,index);
    }
}

int main(){
    int size = Width * Width * sizeof(int);
    int a[Width][Width], b[Width][Width], *devA, * devB;
    srand(1234);
    printf("Original A array\n");
    for (int i = 0; i < Width; i++){
        for (int j = 0; j < Width; j++){
            a[i][j] = rand() % 1000;
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    
    cudaMalloc((void**)&devA, size);
    cudaMalloc((void**)&devB, size);
    
    cudaMemcpy(devA, a, size, cudaMemcpyHostToDevice);
    
    dim3 dimBlock(T, T);
    dim3 dimGrid(Width/T, Width/T);
    
    vecTranspose<<<dimGrid, dimBlock>>>(devA, devB, Width, size);
    
    cudaMemcpy(b, devB, size, cudaMemcpyDeviceToHost);
    
    cudaFree(devA);
    cudaFree(devB);
    printf("\nNew A array \n");
    for (int i = 0; i < Width; i++){
        for (int j = 0; j < Width; j++){
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
}