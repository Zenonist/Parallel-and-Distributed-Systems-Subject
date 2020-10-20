#include <omp.h>
#include <stdio.h>
int main(int argc, char *argv[]){
    #pragma omp parallel num_threads(4){
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();
        printf("Hello World from thread %d of %d\n", tid, nthreads);
    }
}