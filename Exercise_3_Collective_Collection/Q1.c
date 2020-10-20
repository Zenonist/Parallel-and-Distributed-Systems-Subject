/*
Write a parallel program to find the maximum, minimum, and average values in an
array of integers A[100] using 4 processes as follows:
• Process 0 initializes the array A by the following code fragment
• Process 0 distributes the array A to all processes (including itself) by
MPI_Scatter
• All processes find the local maximum, minimum, and average (sum) values,
and then perform reduction for the global values
• Check the result with the sequential version executed at Process 0
• Hint: Use separate MPI_Reduce for global maximum, minimum and average
values
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int main(int argc, char *argv[]){
    int A[100], rank, size;
    srand(1234); /* Set random seed */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int sizedata = 100 / size;
    int temp[sizedata];
    int min ,Grandmin;
    int max ,Grandmax;
    int sum ,Grandsum;
    for (int i = 0; i < 100; i++){
        A[i] = rand() % 1000; /* Set each element randomly to 0-999 */
    }
    MPI_Scatter((void *)A, sizedata, MPI_INT, (void *)&temp, sizedata ,MPI_INT, 0, MPI_COMM_WORLD);
    min = 9999999;
    max = -9999999;
    sum = 0;
    for (int x = 0; x < (100 / size); x++){
        if (temp[x] < min)
        {
            min = temp[x];
        }
        if (temp[x] > max)
        {
            max = temp[x];
        }
        sum += temp[x];
    }
    sum = sum / (100/size);
    MPI_Reduce(&sum, &Grandsum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Reduce(&min, &Grandmin,1,MPI_INT,MPI_MIN,0,MPI_COMM_WORLD);
    MPI_Reduce(&max, &Grandmax,1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);
    if (rank == 0){
        printf("Sum = %d Min = %d max = %d\n",Grandsum,Grandmin,Grandmax);
    }
    MPI_Finalize();
}
