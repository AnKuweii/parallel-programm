#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	MPI_Init(&argc, &argv);
	int numP, myId;
	MPI_Comm_rank(MPI_COMM_WORLD, &myId);
	MPI_Comm_size(MPI_COMM_WORLD, &numP);

	int next_id = (myId + 1) % numP, prev_id = (myId - 1 + numP) % numP;
	MPI_Request rq_send, rq_recv;

	int a = 1, b;
	MPI_Isend(&a, 1, MPI_INT, next_id, 0, MPI_COMM_WORLD, &rq_send);
	MPI_Irecv(&b, 1, MPI_INT, prev_id, 0, MPI_COMM_WORLD, &rq_recv);
	MPI_Wait(&rq_recv, MPI_STATUS_IGNORE);
	printf("%d receive token %d from %d\n", myId, b, prev_id);
	MPI_Barrier(MPI_COMM_WORLD);

	a = -1;
	MPI_Isend(&a, 1, MPI_INT, prev_id, 0, MPI_COMM_WORLD, &rq_send);
	MPI_Irecv(&b, 1, MPI_INT, next_id, 0, MPI_COMM_WORLD, &rq_recv);
	MPI_Wait(&rq_recv, MPI_STATUS_IGNORE);
	printf("%d receive token %d from %d\n", myId, b, next_id);
	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();
}