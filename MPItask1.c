#pragma warning(disable:4996)
#include <stdio.h>
#include <mpi.h>
#include <malloc.h>
#include <math.h>
main(int argc, char** argv) {
	int my_rank;
	int p;
	int source;
	int dest;
	int tag = 50;
	int i;
	int count;
	char message[100];
	int a;
	int j;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	if (my_rank != 0) {
		sprintf(message, "Greetings from process %d!", my_rank);
		dest = 0;
		MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	}
	else {
		int**a = (char*)malloc(100 * sizeof(char));
		for (source = 1; source < p; source++) {
			MPI_Probe(MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
			MPI_Get_count(&status, MPI_CHAR, &count);
			a[status.MPI_SOURCE] = malloc(count * sizeof(char));
			MPI_Recv(message, 100, MPI_CHAR, status.MPI_SOURCE, tag, MPI_COMM_WORLD, &status);
			for (i = 0; i < strlen(message) + 1; i++) {
				a[status.MPI_SOURCE][i] = message[i];
			}
			printf("%s\n", message);
		}
	}
	MPI_Finalize();
}
