#include "mpi.h"
#include <stdio.h>

//#define N 16
#define N 1024

double mat[N][N];
double vec[N];

int main (int argc, char* argv[])
{
	int rank, size;
	double t1, t2;
	char filename[16];

	// Read matrix and vector data from file
	sprintf(filename, "%d.txt", N);
	FILE *fp = fopen(filename, "r");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf(fp, "%lf", &mat[i][j]);
		}
	}
	for (int i = 0; i < N; i++) {
		fscanf(fp, "%lf", &vec[i]);
	}
	fclose(fp);

	// MPI start
	MPI_Init(&argc, &argv);
	t1 = MPI_Wtime();

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Status status;
	////////////////////////
	// You need to fill here
	////////////////////////
	
	double rdata, local_max, global_max;
	double res[N];
	int local_iter = N / size;
	int start_iter = rank * local_iter;
	int end_iter = start_iter + local_iter;
	for (int i = start_iter; i < end_iter; i++) {
		double mul = 0;
		for (int j = 0; j < N; j++) {
			mul += mat[i][j] * vec[j];
		}
		res[i] = mul;
	}
	local_max = res[start_iter];
	for (int i = start_iter; i < end_iter; i++) {
		if (res[i] > local_max){
			local_max = res[i];
		}
	}
	global_max = local_max;
	if (rank == 0)
	{
		//printf("current max : %lf\n", global_max); 
		for(int source = 1; source<size; source++){

			MPI_Recv(&rdata, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, &status);
			//printf("received : %lf\n", rdata);
			if (rdata>global_max){
				global_max=rdata;
			}
		}
			printf("max value : %lf\n", global_max);
	}
	else {
		MPI_Send(&local_max, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	t2 = MPI_Wtime();
	if (rank == 0)
		printf("Elapsed time for rank 0 is %f\n", t2 - t1);
	if (rank == 1)
		printf("Elapsed time for rank 1 is %f\n", t2 - t1);
        
	MPI_Finalize();
	
	return 0;
}
	     
