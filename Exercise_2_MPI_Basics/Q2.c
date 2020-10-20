/*
2) Write an MPI program with two processes working as follows:
• Process 0 sends an integer number to process 1
• Process 1 calculates the square of the number, and sends the result to process 0
• Process 0 prints out the result.
*/
#include <stdio.h>
#include <math.h>
#include <mpi.h>
int main(int argc, char *argv[]){
    int rank, size, temp ,result;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0){
        scanf("%d",&temp);
        MPI_Send(&temp,1,MPI_INT,1,123,MPI_COMM_WORLD);
        MPI_Recv(&result,1,MPI_INT,1,123,MPI_COMM_WORLD,&status);
        printf("%d\n",result);
    }else{
        int tempdata;
        MPI_Recv(&result,1,MPI_INT,0,123,MPI_COMM_WORLD,&status);
        tempdata = result * result;
        MPI_Send(&tempdata,1,MPI_INT,0,123,MPI_COMM_WORLD);
    }
    MPI_Finalize();
}