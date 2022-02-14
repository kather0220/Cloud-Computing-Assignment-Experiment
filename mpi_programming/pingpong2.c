#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	int rank, size;
	char sdata, rdata;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	for(int i=0; i<11; i++){
		if(rank==1){
			sdata = 'a';
			MPI_Send(&sdata, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
			MPI_Recv(&rdata, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
			printf("%c\n", rdata);
		}else{
			sdata = 'b';
			
		        MPI_Recv(&rdata, 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
			MPI_Send(&sdata, 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
			printf("%c\n", rdata);
		}
	}
	MPI_Finalize();
	return 0;
}
