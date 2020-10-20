/*
Write an MPI program with two processes working as follows:
• Process 0 sends an array of 10 integers to process 1
• Process 1 multiplies 10 to each element in the array, and sends the result array
back to process 0
• Process 0 prints out the result
*/
#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]){
    int rank, size;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0){
        int arr[10];
        for (int i = 0;i < 10;i++){
            scanf("%d",&arr[i]);
        }
        MPI_Send(&arr,10,MPI_INT,1,123,MPI_COMM_WORLD);
        MPI_Recv(&arr,10,MPI_INT,1,123,MPI_COMM_WORLD,&status);
        for (int x = 0;x < 10;x++){
            printf("%d\n",arr[x]);
        }
    }else{
        int temparr[10];
        MPI_Recv(&temparr,10,MPI_INT,0,123,MPI_COMM_WORLD,&status);
        for (int x = 0; x < 10; x++){
            temparr[x] = temparr[x] * 10;
        }
        MPI_Send(&temparr,10,MPI_INT,0,123,MPI_COMM_WORLD);
    }
    MPI_Finalize();
}