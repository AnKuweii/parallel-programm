#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	MPI_Init(&argc, &argv);
	int numP, myId;
	MPI_Comm_rank(MPI_COMM_WORLD, &myId);
	MPI_Comm_size(MPI_COMM_WORLD, &numP);

	int n = atoi(argv[1]);
	MPI_Barrier(MPI_COMM_WORLD);

	double start = MPI_Wtime();

	int myCount = 0;
	int total;
	int prime;

	for(int i = 2 + myId; i <= n; i += numP) {
		prime = 1;
		for(int j = 2; j < i; ++j) {
			if(i % j == 0) {
				prime = 0;
				break;
			}
		}
		myCount += prime;
	}

	MPI_Reduce(&myCount, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	double end = MPI_Wtime();
	if(!myId) {
		printf("%d primes between 1 and %d\n", total, n);
		printf("Time with %d processes: %.3lf seconds\n", numP, end - start);
	}
	MPI_Finalize();
}