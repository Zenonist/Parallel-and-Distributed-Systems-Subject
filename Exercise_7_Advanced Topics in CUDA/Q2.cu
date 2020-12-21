#include <stdio.h>
#define N 1024
#define T 256

__global__ void FindFreq(int *devA, int target , int *result){
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < N){
        //printf("%d-%d\n",devA[index],target);
        //printf((int) target == (int) devA[index] ? "true\n" : "false\n");
        if (target == devA[index]){
            atomicAdd(&result[0],1);
        }
    }
    __syncthreads();
}

int main (int argc, char *argv[]){
    int size = N * sizeof (int);
    int A[N] , *devA , *devResult;
    int targetnumber;
    int result[1]; //It should be right because we need to send array[pointer] to Device
    printf("Enter the target number to find the frequency (integer only): ");
    scanf("%d", &targetnumber);
    for (int x = 0; x < N; x++){
        A[x] = rand () % 100;
        printf("%d ",A[x]);
    }
    
    cudaMalloc((void**)&devA, size);
    cudaMalloc((void**)&devResult, 1 * sizeof(int));
    
    cudaMemcpy(devA, A, size, cudaMemcpyHostToDevice);
    
    cudaMemset(devResult, 0, 1 * sizeof(int));
    
    dim3 dimBlock(T);
    dim3 dimGrid(N/T);
    
    FindFreq<<<dimGrid, dimBlock>>>(devA, targetnumber , devResult);
    
    cudaMemcpy(result, devResult, 1 * sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(devA);
    cudaFree(devResult);
    
    printf("\nThe frequency of %d in array: %d",targetnumber, result[0]);
}