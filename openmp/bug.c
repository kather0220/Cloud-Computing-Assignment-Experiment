#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1024
#define M 1024 

int main() {
	
	int nthreads, tid, i, j;
	double *a;

	#pragma omp parallel shared(nthreads) private(i, j, tid, a)
	{
		a = (double *)malloc(N*M*sizeof(double));
		tid=omp_get_thread_num();
		printf("thread %d running\n", tid);
		
		for(i=0; i<N;i++)
			for(j=0; j<M; j++)
				a[i*N+j]= tid + i + j;

		printf("thread %d: last a element %lf\n", tid, a[N*M-1]);
		free(a);
	}
}
