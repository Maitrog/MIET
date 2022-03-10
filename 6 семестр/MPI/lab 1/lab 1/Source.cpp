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
	int msg = 1, recvMsg = -1;
	for (int j = 0; j < M; j++) {
		if (ProcRank == 0)
		{
			for (int i = 1; i < ProcNum; i++)
			{
				MPI_Send(&msg, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				printf("Send %d to process %3d\n", msg, i);
			}
			for (int i = 1; i < ProcNum; i++)
			{
				MPI_Recv(&recvMsg, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
				printf("Receive %d from process %3d\n", recvMsg, i);
			}
		}
		else
		{
			MPI_Recv(&recvMsg, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			printf("Receive %d in process %3d\n", recvMsg, ProcRank);
			msg = recvMsg * ProcRank;
			MPI_Send(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			printf("Send %d to process %3d\n", msg, 0);

		}
	}
	MPI_Finalize();
	return 0;
}
