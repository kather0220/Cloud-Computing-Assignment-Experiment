#include <stdio.h>
#include <omp.h>

int main() {

	int id;
	printf("%d\n", omp_get_max_threads());

	#pragma omp parallel
	{
		id = omp_get_thread_num();
		int np = omp_get_num_threads();
		printf("Hello world! I am %d of %d\n", id, np);
	}
	return 0;
}
