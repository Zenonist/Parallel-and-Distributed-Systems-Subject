#include <stdio.h>
#include <mpi.h>
#define ll long long
int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Status status;
    ll int interval, left, right, statusstart = -1;
    ll int number, start, end, sum, GrandTotal = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("left: ");
        fflush(stdout);
        scanf("%lld", &left);
        printf("right: ");
        fflush(stdout);
        scanf("%lld", &right);
    }
    MPI_Bcast(&left, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&right, 1, MPI_INT, 0, MPI_COMM_WORLD);
    interval = (right - left + 1) / (size - 1);
    start = (rank - 1) * interval + left;
    end = start + interval - 1;
    if (rank == (size - 1))
    { /* for last block */
        end = right;
    }
    sum = 0; /*Sum locally on each proc*/
    for (number = start; number <= end; number++)
    {
        sum = sum + number;
        //printf("Rank %d Number %lld Sum %lld\n", rank, number, sum);
    }
    MPI_Reduce(&sum, &GrandTotal, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("GrandTotal = %lld\n", GrandTotal);
    }
    MPI_Finalize();
}