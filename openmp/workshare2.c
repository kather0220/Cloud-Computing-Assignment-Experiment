#include <stdio.h>
#include <omp.h>

#define CHUNKSIZE 1
#define N 10

int main() {

	int nthreads, id, tid, i, chunk;
	float a[N], b[N], c[N];

	for(i=0; i<N; i++){
		a[i]=i;
		b[i]=i;
	}

	chunk = CHUNKSIZE;

	#pragma omp parallel shared(a, b, c, nthreads, chunk) private(tid, i)
	{
		tid = omp_get_thread_num();
		if(tid==0){
			nthreads=omp_get_num_threads();
			printf("%d", nthreads);
		}
		printf("Thread %d starting\n", tid);


		#pragma omp sections nowait
		{
			#pragma omp section
			{
				printf("Thread %d running section 1\n", tid);
				for(i=0; i<N;i++){
					c[i] = a[i]+b[i];
					printf("Thread %d c[%d] = %f\n", tid, i, c[i]);
				}
			}
			#pragma omp section
                        {
                                printf("Thread %d running section 2\n", tid);
                                for(i=0; i<N;i++){
                                        c[i] = a[i]+b[i];
                                        printf("Thread %d c[%d] = %f\n", tid, i, c[i]);
                                }
                        }

		} // implicit barrier
		printf("done\n");
	}
	return 0;
}
