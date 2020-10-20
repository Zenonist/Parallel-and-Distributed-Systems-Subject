/*
Given arrays of integers A[100] and B[100], write an MPI program to construct
C[100], which each element C[i] = A[i] + B[i], using MPI_Scatter and
MPI_Gather on 2 processes.
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int rank, size;
    int A[100], B[100], C[100], atemp[50], btemp[50], result[50];
    srand(1234);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int arrsize = 100 / size;
    for (int i = 0; i < 100; i++){
        A[i] = rand() % 1000;
        B[i] = rand() % 1000;
    }
    MPI_Scatter((void *)A, arrsize, MPI_INT, (void *)&atemp, arrsize, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter((void *)B, arrsize, MPI_INT, (void *)&btemp, arrsize, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0){
        for (int x = 0; x < arrsize; x++){
            result[x] = atemp[x] + btemp[x];
        }
    }else{
        for (int x = 0; x < arrsize; x++){
            result[x] = atemp[x] + btemp[x];
        }
    }
    MPI_Gather(&result, arrsize, MPI_INT, (void *)&C, arrsize, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0){
        for (int x = 0; x < 100; x++){
            printf("Result = %d\n",C[x]);
        }  
    }
    MPI_Finalize();
}