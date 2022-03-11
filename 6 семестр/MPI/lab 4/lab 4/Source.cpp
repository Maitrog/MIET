#include <iostream>
#include <cstdlib>
#include <cmath>
#include <mpi.h>
#include <cstddef>


constexpr int MAX_SIZE = 1000;
constexpr int SIZE = 10;

struct LONG_INT {
	int size;
	int base;
	int number[MAX_SIZE];
};

LONG_INT multiply(LONG_INT left, LONG_INT right);
void printLongInt(LONG_INT x);
int getNewSize(LONG_INT x);

int main(int argc, char** argv) {

	MPI_Init(&argc, &argv);

	int rank, size;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int n_structure_per_process = 4;
	int n_structure = n_structure_per_process * size;
	LONG_INT* data = nullptr;

	if (rank == 0)
	{
		srand(rank * 10);
		data = new LONG_INT[n_structure];
		for (int i = 0; i < n_structure; ++i) {
			data[i].size = SIZE;
			data[i].base = 10;
			for (int j = 0; j < MAX_SIZE; ++j) {
				data[i].number[j] = (j < data[i].size ? rand() % 10 : 0);
			}
			std::cout << i << ": ";
			printLongInt(data[i]);
			std::cout << std::endl;
		}
	}

	MPI_Aint displacements[3] = { offsetof(LONG_INT, size), offsetof(LONG_INT, base), offsetof(LONG_INT, number) };
	int block_lengths[3] = { 1, 1, MAX_SIZE };
	MPI_Datatype types[3] = { MPI_INT, MPI_INT, MPI_INT };
	MPI_Datatype custom_dt;

	MPI_Type_create_struct(3, block_lengths, displacements, types, &custom_dt);
	MPI_Type_commit(&custom_dt);

	LONG_INT* gathered_data = nullptr;
	LONG_INT* scatter_data = new LONG_INT[n_structure_per_process];
	LONG_INT result;
	result.size = 1;
	result.base = 10;
	for (int j = 0; j < MAX_SIZE; ++j)
		result.number[j] = (j == 0 ? 1 : 0);

	if (rank == 0)
		gathered_data = new LONG_INT[size];

	MPI_Scatter(data, n_structure_per_process, custom_dt, scatter_data, n_structure_per_process, custom_dt, 0, MPI_COMM_WORLD);
	for (int i = 0; i < n_structure_per_process; i++) {
		result = multiply(result, scatter_data[i]);
	}

	MPI_Gather(&result, 1, custom_dt, gathered_data, 1, custom_dt, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		result = gathered_data[0];
		for (int i = 1; i < size; ++i) {
			result = multiply(result, gathered_data[i]);
		}
		printLongInt(result);
		std::cout << std::endl;
	}

	MPI_Finalize();

	return 0;
}

LONG_INT multiply(LONG_INT left, LONG_INT right) {
	LONG_INT result;
	result.size = left.size + right.size;
	result.base = 10;
	for (int j = 0; j < MAX_SIZE; ++j)
		result.number[j] = 0;

	for (int i = 0; i < left.size; i++) {
		int carry = 0;
		for (int j = 0; j < right.size || carry != 0; j++) {
			int cur = result.number[i + j] + left.number[i] * (j < right.size ? right.number[j] : 0) + carry;
			result.number[i + j] = cur % base;
			carry = cur / result.base;
		}
	}
	result.size = getNewSize(result);
	return result;
}

int getNewSize(LONG_INT x) {
	int newSize = x.size;
	while (x.number[newSize - 1] == 0) {
		newSize--;
	}
	return newSize;
}

void printLongInt(LONG_INT x) {
	for (int i = x.size - 1; i >= 0; --i) {
		std::cout << x.number[i];
	}
}
