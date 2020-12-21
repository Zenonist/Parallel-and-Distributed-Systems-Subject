#include <stdio.h>
#define Width 16
#define TILE_WIDTH 4

__global__ void MatrixCalSum(int *devA, int *devB){
    int row = blockIdx.y * TILE_WIDTH + threadIdx.y;
    int col = blockIdx.x * TILE_WIDTH + threadIdx.x;
    atomicAdd(&devB[row], devA[Width*col+row]);
    atomicAdd(&devB[col+8], devA[Width*col+row]);
    

}
int main(int argc, char *argv[]){
    int size = Width * Width * sizeof(int);
    int A[Width][Width] , Result[Width], *devA , *devB;
    for (int x = 0;x < Width; x++){
        for (int y = 0; y < Width; y++){
            A[x][y] = rand() % 1000;
            printf("%d ", A[x][y]);
        }
        printf("\n");
    }
    cudaMalloc((void **)&devA,size);
    cudaMalloc((void **)&devB, Width * sizeof(int));
    
    cudaMemcpy(devA, A, size, cudaMemcpyHostToDevice);
    
    cudaMemset(devB, 0, Width * sizeof(int));
    
    dim3 dimBlock(TILE_WIDTH);
    dim3 dimGrid(Width/TILE_WIDTH);
    
    MatrixCalSum<<<dimGrid, dimBlock>>>(devA, devB);
    
    cudaMemcpy(Result, devB, Width * sizeof(int), cudaMemcpyDeviceToHost);
    
    cudaFree(devA);
    cudaFree(devB);
    
    /*for (int x = 0; x < Width + 1; x++){
        for (int y = 0; y < Width; y++){
            printf("%d ",A[x][y]);
            if (y == Width - 1 && x != Width){
                printf("| %d\n",Result[y]);
            }
            if (x == Width){
                printf("%d ",Result[8 + y]);
            }
        }
    }*/
    for (int x = 0; x < 16;x++){
        printf("%d ",Result[x]);
    }
}