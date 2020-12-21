#include <stdio.h>

#define Width 32 // size of Width x Width matrix
#define TILE_WIDTH 16

__global__ void MatrixMulKernel (float* Md, float* Nd, float* Pd){
    __shared__ float shared_A[TILE_WIDTH][TILE_WIDTH];
    __shared__ float shared_B[TILE_WIDTH][TILE_WIDTH];
    
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    //Pvalue is used to store the element of the output matrix
    // that is computed by the thread
    
    float Pvalue = 0;
    for (int k = 0; k < Width/TILE_WIDTH; k++){
        // y = row , x = col
        shared_A[threadIdx.y][threadIdx.x] = Md[row*Width+(k * TILE_WIDTH + threadIdx.x)];
        shared_B[threadIdx.y][threadIdx.x] = Nd[(k * TILE_WIDTH + threadIdx.y)*Width+col];
        __syncthreads(); // similar to barrier
        
        for (int x = 0; x < TILE_WIDTH; x++){
            Pvalue += shared_A[threadIdx.y][x] * shared_B[x][threadIdx.x];
        }
        __syncthreads(); // similar to barrier
    }
    Pd[row*Width+col] = Pvalue;
}

int main (int argc, char *argv[]){
    int i,j;
    int size = Width * Width * sizeof(float);
    float M[Width][Width], N[Width][Width], P[Width][Width];
    float* Md, *Nd, *Pd;
    
    for (i = 0; i < Width; i++){
        for (j = 0; j < Width; j++){
            M[i][j] = 1; N[i][j] = 2;
        }
    }
    
    cudaMalloc( (void**)&Md, size);
    cudaMalloc( (void**)&Nd, size);
    cudaMalloc( (void**)&Pd, size);
    
    cudaMemcpy( Md, M, size, cudaMemcpyHostToDevice);
    cudaMemcpy( Nd, N, size, cudaMemcpyHostToDevice);
    
    //Setup the execution configuration
    dim3 dimBlock(TILE_WIDTH, TILE_WIDTH);
    dim3 dimGrid(Width/TILE_WIDTH, Width/TILE_WIDTH);
    
    //Launch the device computation threads!
    MatrixMulKernel<<<dimGrid, dimBlock>>>(Md, Nd, Pd);
    
    //Read P from the device
    cudaMemcpy( P, Pd, size, cudaMemcpyDeviceToHost);
    
    //Free device matrices
    cudaFree( Md);
    cudaFree( Nd);
    cudaFree( Pd);
    
    for (i = 0; i < Width; i++){
        for (j = 0; j < Width; j++){
            printf("%.2f ",P[i][j]);
        }
        printf("\n");
    }
}