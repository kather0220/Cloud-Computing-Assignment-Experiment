#include <stdio.h>
#include <omp.h>

#define CHUNKSIZE 2 
#define N 14

int main() {

	int nthreads, id, tid, i, chunk;
	float a[N], b[N], c[N];

	for(i=0; i<N; i++){
		a[i]=i;
		b[i]=i;
	}
	omp_set_num_threads(2);

	chunk = CHUNKSIZE;

	#pragma omp parallel if(N>=12) shared(a, b, c, nthreads, chunk) private(tid, i)
	{
		tid = omp_get_thread_num();
		if(tid==0){
			nthreads=omp_get_num_threads();
			printf("%d", nthreads);
		}
		printf("Thread %d starting\n", tid);


		#pragma omp for schedule(static, chunk)
		for(i = 0; i<N; i++) {
			c[i] = a[i] + b[i];
			printf("thread %d: c[%d] at %f\n", tid, i, c[i]);
			}
	}
	return 0;
}
