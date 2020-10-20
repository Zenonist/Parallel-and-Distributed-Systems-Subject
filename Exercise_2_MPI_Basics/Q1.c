/*
Draw a task graph of the following instructions and determine which tasks can be
executed in parallel.
T1: a = cos(1.0);
T2: b = sin(2.0);
T3: c = a + b;
T4: d = a - b;
T5: e = c*d;
*/
#include <stdio.h>
#include <math.h>
#include <mpi.h>
int main(int argc, char *argv[]){
    int rank,size;
    float a,b,c,d,e;
    MPI_status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if (rank == 0) {
        //Rank 1
        MPI_Recv(&a, 1,MPI_FLOAT,1,123,MPI_COMM_WORLD, &status);
        //Rank 2
        MPI_Recv(&b, 1,MPI_FLOAT,2,123,MPI_COMM_WORLD, &status);
        //Rank 3
        MPI_Send(&a, 1,MPI_FLOAT,3,123,MPI_COMM_WORLD);
        MPI_Send(&b, 1,MPI_FLOAT,3,123,MPI_COMM_WORLD);
        MPI_Recv(&c, 1,MPI_FLOAT,3,123,MPI_COMM_WORLD, &status);
        //Rank 4
        MPI_Send(&a, 1,MPI_FLOAT,4,123,MPI_COMM_WORLD);
        MPI_Send(&b, 1,MPI_FLOAT,4,123,MPI_COMM_WORLD);
        MPI_Recv(&d, 1,MPI_FLOAT,4,123,MPI_COMM_WORLD, &status);
        //Rank 5
        MPI_Send(&c, 1,MPI_FLOAT,5,123,MPI_COMM_WORLD);
        MPI_Send(&d, 1,MPI_FLOAT,5,123,MPI_COMM_WORLD);
        MPI_Recv(&e, 1,MPI_FLOAT,5,123,MPI_COMM_WORLD, &status);
        //result
        printf("T1: %d T2: %d T3: %d T4: %d T5: %d\n",a,b,c,d,e);
    }else{
        if (rank == 1){
            int result = cosf(1.0);
            MPI_Send(&result, 1,MPI_FLOAT,0,MPI_COMM_WORLD);
        }else if (rank == 2){
            int result = sinf(2.0);
            MPI_Send(&result, 1,MPI_FLOAT,0,MPI_COMM_WORLD);
        }else if (rank == 3){
            int arr[2] , result;
            for (int x = 0;x < 2;x++){
                MPI_Recv(&arr[x],1,MPI_FLOAT,0,MPI_COMM_WORLD,&status);
            }
            result = arr[0] + arr[1];
            MPI_Send(&result, 1,MPI_FLOAT,0,MPI_COMM_WORLD);
        }else if (rank == 4){
            int arr[2] , result;
            for (int x = 0;x < 2;x++){
                MPI_Recv(&arr[x],1,MPI_FLOAT,0,MPI_COMM_WORLD, &status);
            }
            result = arr[0] - arr[1];
            MPI_Send(&result , 1,MPI_FLOAT,0,MPI_COMM_WORLD);
        }else{
            int arr[2] , result;
            for (int x = 0;x < 2;x++){
                MPI_Recv(&arr[x],1,MPI_FLOAT,0,MPI_COMM_WORLD, &status);
            }
            result = arr[0] * arr[1];
            MPI_Send(&result , 1,MPI_FLOAT,0,MPI_COMM_WORLD);
        }
    }
}