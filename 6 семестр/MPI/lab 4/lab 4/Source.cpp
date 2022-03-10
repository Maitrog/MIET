#include <iostream>
#include <cstdlib>
#include <cmath>
#include <mpi.h>
#include <cstddef>

constexpr int SIZE = 10;
struct LONG_INT {
	int size;
	int base;
	int number[SIZE];
};

int main(int argc, char** argv) {

	MPI_Init(&argc, &argv);

	int rank, size;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	constexpr int n_structure_per_process = 4; // M = 5

	// Random generator init
	srand(rank * 10);

	// Creating the dataset
	LONG_INT data[n_structure_per_process];

	// Generating the data
	for (int i = 0; i < n_structure_per_process; ++i) {
		// Terrible way of generating random numbers, don't reproduce this at home
		data[i].size = SIZE;
		data[i].base = 1;
		for (int j = 0; j < SIZE; ++j)
			data[i].number[j] = (j < data[i].size ? rand() % 10 : 0.0);
	}

	// 1- Here, create all the properties to call MPI_Type_create_struct
	MPI_Aint displacements[3] = {offsetof(LONG_INT, size), offsetof(LONG_INT, base), offsetof(LONG_INT, number)};
	int block_lengths[3] = {1, 1, SIZE};
	MPI_Datatype types[3] = {MPI_INT, MPI_INT, MPI_INT};
	MPI_Datatype custom_dt;
	
	// 2- Create the type, and commit it
	MPI_Type_create_struct(3, block_lengths, displacements, types, &custom_dt);
	MPI_Type_commit(&custom_dt);
	// Gathering the data
	LONG_INT* gathered_data = nullptr;

	if (rank == 0)
		gathered_data = new LONG_INT[n_structure_per_process * size];

	MPI_Gather(data, n_structure_per_process, custom_dt,
		gathered_data, n_structure_per_process, custom_dt, 0, MPI_COMM_WORLD);

	// And printing it
	if (rank == 0) {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < n_structure_per_process; ++j) {
				int data_id = i * n_structure_per_process + j; // Linear index

				std::cout << "Data structure " << data_id << " : [";
				int N = gathered_data[data_id].size;

				for (int k = 0; k < N; ++k) {
					std::cout << gathered_data[data_id].number[k] << (k == N - 1 ? "]" : "; ");
				}
				std::cout << std::endl;
			}
		}
	}


	MPI_Finalize();

	return 0;
}
