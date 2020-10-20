#include <stdio.h>
#define N 256
#define T 256
__global__ void reverseArray(int *A ,int *B){
    int i = threadIdx.x;
    B[i] = A[(N - 1) - i];
}
int main (int argc, char *argv[]){
    int i;
    int size = N * sizeof (int);
    int a[N], b[N], *devA, *devB;
    printf("Original A array\n");
    for (i = 0; i < N; i++){
        a[i] = i;
	printf("%d ",a[i]);
    }
    cudaMalloc( (void**)&devA,size);
    cudaMalloc( (void**)&devB,size);
    
    cudaMemcpy( devA, a, size, cudaMemcpyHostToDevice);
    
    reverseArray<<<1,T>>>(devA,devB);
    
    cudaMemcpy( b, devB, size, cudaMemcpyDeviceToHost);
    cudaFree(devA);
    cudaFree(devB);
    printf("\nNew A array \n");
    for (i = 0;i < N; i++){
        printf("%d ",b[i]);
    }
    printf("\n");
}