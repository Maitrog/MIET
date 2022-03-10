#define	_CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mpi.h"
#include <iostream>

int main(int argc, char** argv)
{
	int M = 4;
	int ProcNum, ProcRank;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	int msg = 1, recvMsg = 1;
	for (int j = 0; j < M; j++) {
		MPI_Bcast(&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);
		if (ProcRank == 0)
		{
			printf("Send %d from 0 to all process\n", msg);
		}
		else
		{
			printf("Receive %d in process %3d\n", msg, ProcRank);
			msg = msg * ProcRank;
			printf("Send %d from %d to process %3d\n", msg, ProcRank, 0);
		}
		MPI_Reduce(&msg, &recvMsg, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
		if (ProcRank == 0) {
			printf("Result: %d\n", recvMsg);
		}
	}
	MPI_Finalize();
	return 0;
}
