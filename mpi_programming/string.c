#include "mpi.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
	int rank, size;
	char sdata[255];
	char rdata[255];
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank==1){
		strcpy(sdata, "I love Ewha Womans University");
		MPI_Send(sdata, 255, MPI_CHAR, 0, 0,  MPI_COMM_WORLD);
		printf("Sending %s\n", sdata);
	}else{
		MPI_Recv(rdata, 255, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
		printf("Receiving %s\n", rdata);
	}
	MPI_Finalize();
	return 0;
}
