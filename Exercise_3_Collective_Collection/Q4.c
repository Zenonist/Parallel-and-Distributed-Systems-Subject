/*
Given a matrix A[8][8] with some random values, write an MPI program to
calculate the summation of all elements using only MPI collective communication
on 8 processes. (MPI_Send/MPI_Recv are not allowed)
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int main(int argc, char *argv[]){
    int rank, size;
    int arr[8][8];
    int temparr[8],sum = 0,Totalsum;
    srand(1234);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8;j++){
            arr[i][j] = rand() % 1000;
        }
    }
    MPI_Scatter((void *)arr,8,MPI_INT,(void *)&temparr,8,MPI_INT,0,MPI_COMM_WORLD);
    for (int x = 0; x < 8; x++){
        sum = temparr[x] + sum;
    }
    MPI_Reduce(&sum,&Totalsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0){
        printf("Total sum is %d\n",Totalsum);
    }
    MPI_Finalize();
}
