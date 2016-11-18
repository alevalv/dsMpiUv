#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char **argv) {
	int my_rank, p, tag = 0;
	char msg[20];
	char resp[20];
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	if (my_rank == 0) {
		strcpy(msg, "Hello ");
		MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);
		printf("I have sent '%s' to 1", msg);
		MPI_Recv(resp, 20, MPI_CHAR, 1, tag, MPI_COMM_WORLD, &status);
		printf("I have received '%s' from 1", resp);
	} else if (my_rank == 1) {
		MPI_Recv(msg, 20, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
		printf("I have received '%s' from 0", msg);
		strcpy(resp, "HELLO ");
		MPI_Send(resp, strlen(resp) + 1, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
		printf("I have sent '%s' to 0", resp);
	}
	MPI_Finalize();
}
