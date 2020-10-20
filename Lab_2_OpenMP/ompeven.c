#include <omp.h>
#include <stdio.h>

int main(){
	int sum = 0;
	#pragma omp parallel for reduction(+:sum)
	for (int x = 0; x <= 1000; x++){
		if (x % 2 == 0){
			sum = sum + x;
		}
	}
	printf("%d\n",sum);
}