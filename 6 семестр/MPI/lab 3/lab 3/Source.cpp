#define	_CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mpi.h"
#include <iostream>

void DataInitialize(int* array, int size);
int main(int argc, char** argv)
{
	int M = 4;
	int ProcNum, ProcRank;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	int* msg = new int[ProcNum], *recvMsg = new int[ProcNum];
	DataInitialize(msg, ProcNum);
	DataInitialize(recvMsg, ProcNum);

	for (int j = 0; j < M; j++) {
		MPI_Scatter(msg, 1, MPI_INT, recvMsg, 1, MPI_INT, 0, MPI_COMM_WORLD);
		if (ProcRank == 0)
		{
			printf("Send %d from 0 to all process\n", msg[ProcRank]);
		}
		else
		{
			printf("Receive %d in process %3d\n", recvMsg[0], ProcRank);
			recvMsg[0] = recvMsg[0] * ProcRank;
			printf("Send %d from %d to process %3d\n", recvMsg[0], ProcRank, 0);
		}
		MPI_Gather(recvMsg, 1, MPI_INT, msg, 1, MPI_INT, 0, MPI_COMM_WORLD);
		if (ProcRank == 0) {
			int result = 0;
			for (int i = 0; i < ProcNum; i++) {
				result += msg[i];
			}
			printf("Result: %d\n", result);
		}
	}
	MPI_Finalize();

	delete[] msg;
	delete[] recvMsg;
	return 0;
}

void DataInitialize(int* array, int size) {
	for (int i = 0; i < size; i++) {
		array[i] = 1;
	}
}