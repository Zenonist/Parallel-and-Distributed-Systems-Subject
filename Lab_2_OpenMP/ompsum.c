#include <stdio.h>
#include <omp.h>
int main() {
    int i;
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (i=1; i <= 1000; i++)
        sum = sum + i;
    printf("%d\n",sum);
}