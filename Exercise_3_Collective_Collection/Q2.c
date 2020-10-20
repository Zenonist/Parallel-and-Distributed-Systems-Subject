/*
Parallel search
• Create an array of random integers in Process 0
• Distribute distinct part of the array to all processes
• Process 0 receives an input integer i from a user, and broadcasts it to all.
• Count (in parallel) the number of elements in the array that is less than the
input integer i. Use MPI_reduce to complete this step.
• Display the result
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define ll long long
int main(int argc, char *argv[]){
    int rank,size,arrsize = 100;
    int arr[arrsize];
    srand(1234);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int distibutedsized = arrsize/size,count = 0,temp[distibutedsized];
    ll int Totalcount, userinput;
    if (rank == 0){
        //int arr[100];
        for (int x = 0; x < arrsize; x++){
            arr[x] = rand() % 1000;
        }
        scanf("%lld",&userinput);
    }
    MPI_Scatter((void *)arr,distibutedsized,MPI_INT, (void *)&temp,distibutedsized,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&userinput, 1, MPI_INT, 0, MPI_COMM_WORLD);
    for (int x = 0;x < distibutedsized;x++){
        //printf("%lld %d %d\n",userinput,temp[x],rank);
        if (temp[x] < userinput){
            count ++;
        }
    }
    MPI_Reduce(&count,&Totalcount,1,MPI_INT,MPI_SUM,0, MPI_COMM_WORLD);
    if (rank == 0){
        printf("The Total count is %lld\n",Totalcount);
    }
    MPI_Finalize();
}