#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 100
int main(int argc, char* argv) {
	omp_set_num_threads(8);//set number of threads here
	int i, j, k;
	double sum;
	double start, end; // used for timing
	double A[N][N], B[N][N], C[N][N];
#pragma omp parallel
	{
	#pragma omp for
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				A[i][j] = j * 1;
				B[i][j] = i * j + 2;
				C[i][j] = j - i * 2;
			}
		}
		start = omp_get_wtime(); //start time measurement
	#pragma omp for
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				sum = 0;
				for (k = 0; k < N; k++) {
					sum += A[i][k] * B[k][j];
				}
				C[i][j] = sum;
			}
		}
	}
	end = omp_get_wtime(); //end time measurement
	printf("Time of computation: %f seconds\n", end - start);
	return(0);
}

/*
1 thread
1st trial : 0.004094 seconds
2nd trial : 0.004280 seconds
3rd trial : 0.004082 seconds
4th trial : 0.006183 seconds
5th trial : 0.005521 seconds

-> average : 0.0047698seconds

2 threads
1st trial : 0.028523 seconds
2nd trial : 0.016465 seconds
3rd trial : 0.025708 seconds
4th trial : 0.026005 seconds
5th trial : 0.028691 seconds

-> average : 0.0250784seconds

4 threads
1st trial : 0.024004 seconds
2nd trial : 0.024683 seconds
3rd trial : 0.024132 seconds
4th trial : 0.016454 seconds
5th trial : 0.020489 seconds

-> average : 0.0219524seconds

8 threads
1st trial : 0.018826 seconds
2nd trial : 0.017513 seconds
3rd trial : 0.018350 seconds
4th trial : 0.017984 seconds
5th trial : 0.018428 seconds

-> average : 0.0182202seconds
*/