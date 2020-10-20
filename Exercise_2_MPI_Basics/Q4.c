/*
Create an MPI program with 1 master and 8 slave processes. The master process
initializes an 8x8 matrix A, which each element Ai,j = i + j as shown below. Then, the
master sends a distinct row of matrix A to each slave. Each slave calculates the
summation of all elements in the row it has received from the master. Finally, all
slaves send back the results to the master for aggregation into the total summation. 
*/
#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]){
    int rank,size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0){
        int arr[8][8],result[8],sum = 0;
        for (int x = 0;x < 8;x++){
            for (int y = 0;y < 8;y++){
                arr[x][y] = x + y;
            }
        }
        for (int x = 1;x < 9;x++){
            MPI_Send(&arr[x-1],8,MPI_INT,x,123,MPI_COMM_WORLD);
        }
        for (int x = 0;x < 8;x++){
            MPI_Recv(&result[x],1,MPI_INT,x+1,123,MPI_COMM_WORLD, &status);
            sum += result[x];
        }
        printf("%d\n",sum);
    }else{
        int arr[8];
        int result = 0;
        MPI_Recv(&arr,8,MPI_INT,0,123,MPI_COMM_WORLD, &status);
        for (int x = 0;x < 8;x++){
            result += arr[x];
        }
        MPI_Send(&result,1,MPI_INT,0,123,MPI_COMM_WORLD);
    }
    MPI_Finalize();
}