#include <stdio.h>

#define N 64
#define T 16

__global__ void RankSort (int *devA, int *devB){
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int temp = devA[index];
    
    int count = 0;
    for (int x = 0; x < N; x++){
        // We need index > x because we want to move the duplicate number to next index.
        if (temp > devA[x] || temp == devA[x] && index > x){
            count++;
        }
    }
    devB[count] = temp;
}

int main (int argc, char *argv[]){
    int a[N], *devA, *devB;
    int size = N * sizeof (int);
    printf("Orgianal A array \n");
    for (int x= 0; x < N; x++){
        a[x] = rand () % 100;
        printf ("%d ",a[x]);
    }
    printf("\n");
    cudaMalloc( (void**)&devA, size);
    cudaMalloc( (void**)&devB, size);
    
    cudaMemcpy( devA, a, size, cudaMemcpyHostToDevice);
    
    dim3 dimBlock(T);
    dim3 dimGrid(N/T);
    
    RankSort<<<dimGrid, dimBlock>>>(devA,devB);
    
    cudaMemcpy(a, devB, size, cudaMemcpyDeviceToHost);
    
    cudaFree(devA);
    cudaFree(devB);
    
    printf("\nnew A array\n");
    for (int x = 0; x < N; x++){
        printf("%d ",a[x]);
    }
    printf("\n");
}