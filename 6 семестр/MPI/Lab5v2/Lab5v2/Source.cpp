#include <iostream>
#include <queue>
#include <set>
#include <cstdlib>
#include <cmath>
#include <mpi.h>
#include <cstddef>
#include <complex.h>

#define master 0
#define from_master 0
#define from_slave 1
#define N 3
#define A 4

constexpr int MAX_SIZE = 8;
constexpr int SIZE = 8;

struct COMPLEX_MATRIX {
	int row;
	int column;
	_complex matrix[MAX_SIZE][MAX_SIZE];

	COMPLEX_MATRIX& operator=(const COMPLEX_MATRIX& matrix) {
		this->row = matrix.row;
		this->column = matrix.column;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				this->matrix[i][j] = matrix.matrix[i][j];
			}
		}
		return *this;
	}
};

COMPLEX_MATRIX createMatrix(int row, int column);
int getNormalizedMatrixSize(const int& rowLeftMatrix, const int& rowRightMatrix, const int& colLeftMatrix, const int& colRightMatrix);
void resizeMatrix(COMPLEX_MATRIX& matrix, const int& newRow, const int& newCol);
COMPLEX_MATRIX Multiply(COMPLEX_MATRIX& left, COMPLEX_MATRIX& right);
void createZeroMatrix(COMPLEX_MATRIX& matrix, const int& row, const int& col);
COMPLEX_MATRIX createIdentityMatrix(const int& row, const int& col);
COMPLEX_MATRIX* getRange(COMPLEX_MATRIX* matrixes, int start, int count);
void printMatrix(COMPLEX_MATRIX* matrix);

_complex operator+(const _complex left, const _complex right);
_complex operator-(const _complex left, const _complex right);
_complex operator*(const _complex left, const _complex right);
_complex operator+=(_complex& left, const _complex right);

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	MPI_Status status;
	int rank, size;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	std::queue<COMPLEX_MATRIX> matrixes;
	COMPLEX_MATRIX* fromRoot = new COMPLEX_MATRIX[0];
	int* matrixCount = new int[size - 1];

	srand(rank * 10);

#pragma region InitializeMatrix

	if (rank == 0) {
		getchar();
		for (int i = 0; i < A; i++) {
			matrixes.push(createMatrix(SIZE, SIZE));
		}
		int tmp = A;
		while (tmp % 8 != 0) {
			matrixes.push(createIdentityMatrix(SIZE, SIZE));
			tmp++;
		}
	}

#pragma endregion

#pragma region CreateCustomType

	MPI_Aint displacements[3] = { offsetof(COMPLEX_MATRIX, row), offsetof(COMPLEX_MATRIX, column), offsetof(COMPLEX_MATRIX, matrix) };
	int block_lengths[3] = { 1, 1, MAX_SIZE * MAX_SIZE };
	MPI_Datatype types[3] = { MPI_INT, MPI_INT, MPI_DOUBLE_COMPLEX };
	MPI_Datatype custom_dt;

	MPI_Type_create_struct(3, block_lengths, displacements, types, &custom_dt);
	MPI_Type_commit(&custom_dt);

#pragma endregion

	MPI_Group world_group;
	MPI_Comm_group(MPI_COMM_WORLD, &world_group);

	int ranks12[2] = { 1, 2 };
	int ranks34[2] = { 3, 4 };
	int ranks13[2] = { 1, 3 };

	MPI_Group group12, group34, group13;
	MPI_Group_incl(world_group, 2, ranks12, &group12);
	MPI_Group_incl(world_group, 2, ranks34, &group34);
	MPI_Group_incl(world_group, 2, ranks13, &group13);

	MPI_Comm comm12, comm34, comm13;
	MPI_Comm_create(MPI_COMM_WORLD, group12, &comm12);
	MPI_Comm_create(MPI_COMM_WORLD, group34, &comm34);
	MPI_Comm_create(MPI_COMM_WORLD, group13, &comm13);

	int proc_num12, proc_num34, proc_num13, proc_rank12, proc_rank34, proc_rank13;
	if (comm12 != MPI_COMM_NULL) {
		MPI_Comm_size(comm12, &proc_num12);
		MPI_Comm_rank(comm12, &proc_rank12);
	}

	if (comm34 != MPI_COMM_NULL) {
		MPI_Comm_size(comm34, &proc_num34);
		MPI_Comm_rank(comm34, &proc_rank34);
	}

	if (comm13 != MPI_COMM_NULL) {
		MPI_Comm_size(comm13, &proc_num13);
		MPI_Comm_rank(comm13, &proc_rank13);
	}

	std::set<int> masters;
	COMPLEX_MATRIX master_ans = createIdentityMatrix(SIZE, SIZE);


	if (rank == master) {
		std::cout << matrixes.size() << '\n';
	}

	int times = matrixes.size() / 8;

	MPI_Bcast(&times, 1, MPI_INT, master, MPI_COMM_WORLD);

	for (int i = 0; i < times; i++) {
		COMPLEX_MATRIX c0;
		masters.clear();
		if (rank == master) {
			for (int i = 0; i < size - 1; i++) {
				COMPLEX_MATRIX x;
				x = matrixes.front();
				matrixes.pop();

				COMPLEX_MATRIX y;
				y = matrixes.front();
				matrixes.pop();

				MPI_Send(&(x), 1, custom_dt, i + 1, from_master, MPI_COMM_WORLD);
				MPI_Send(&(y), 1, custom_dt, i + 1, from_master, MPI_COMM_WORLD);
			}
		}
		else {
			COMPLEX_MATRIX x;
			COMPLEX_MATRIX y;

			c0 = createIdentityMatrix(SIZE, SIZE);

			MPI_Recv(&(x), 1, custom_dt, master, from_master, MPI_COMM_WORLD, &status);
			MPI_Recv(&(y), 1, custom_dt, master, from_master, MPI_COMM_WORLD, &status);

			c0 = Multiply(x, y);
		}

		COMPLEX_MATRIX res = createIdentityMatrix(SIZE, SIZE);
		masters.insert(1);
		masters.insert(3);
		if (masters.find(rank) != masters.end()) {
			COMPLEX_MATRIX get;

			if (rank == 1) {
				MPI_Recv(&get, 1, custom_dt, 1, from_slave, comm12, &status);
			}
			else {
				MPI_Recv(&get, 1, custom_dt, 1, from_slave, comm34, &status);
			}

			res = Multiply(get, c0);
		}
		else {
			if (rank == 2) {
				MPI_Send(&c0, 1, custom_dt, 0, from_slave, comm12);
			}
			else if (rank == 4) {
				MPI_Send(&c0, 1, custom_dt, 0, from_slave, comm34);
			}
		}

		masters.erase(3);
		if (masters.find(rank) != masters.end()) {
			COMPLEX_MATRIX get;
			MPI_Recv(&get, 1, custom_dt, 1, from_slave, comm13, &status);

			res = Multiply(res, get);
		}
		else {
			if (rank == 3) {
				MPI_Send(&res, 1, custom_dt, 0, from_slave, comm13);
			}
		}

		if (rank == master) {
			COMPLEX_MATRIX get;
			MPI_Recv(&get, 1, custom_dt, 1, from_slave, MPI_COMM_WORLD, &status);
			master_ans = Multiply(master_ans, get);

			if (i + 1 == times)
			{
				printMatrix(&master_ans);
			}
		}
		else if (rank == 1) {
			MPI_Send(&res, 1, custom_dt, master, from_slave, MPI_COMM_WORLD);
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);

	if (comm12 != MPI_COMM_NULL) MPI_Comm_free(&comm12);
	if (comm34 != MPI_COMM_NULL) MPI_Comm_free(&comm34);
	if (comm13 != MPI_COMM_NULL) MPI_Comm_free(&comm13);
	MPI_Type_free(&custom_dt);

	MPI_Finalize();
	return 0;
}

COMPLEX_MATRIX createMatrix(int row, int column) {
	COMPLEX_MATRIX matrix;
	matrix.row = row;
	matrix.column = column;
	for (size_t i = 0; i < matrix.row; i++) {
		for (size_t j = 0; j < matrix.column; j++)
		{
			//matrix.matrix[i][j] = { (double)rand() + (double)rand() / RAND_MAX, (double)rand() + (double)rand() / RAND_MAX };
			matrix.matrix[i][j] = { 2.0, 0.0 };
		}
	}
	return matrix;
}

int getNormalizedMatrixSize(const int& rowLeftMatrix, const int& rowRightMatrix, const int& colLeftMatrix, const int& colRightMatrix)
{
	int max = std::max(std::max(rowLeftMatrix, rowRightMatrix), std::max(colLeftMatrix, colRightMatrix));
	return max & 0b1 ? (max + 1) : max;
}

void resizeMatrix(COMPLEX_MATRIX& matrix, const int& newRow, const int& newCol)
{
	matrix.row = newRow;
	matrix.column = newCol;
}

COMPLEX_MATRIX Multiply(COMPLEX_MATRIX& left, COMPLEX_MATRIX& right)
{
	int normalizedMatrixSize = getNormalizedMatrixSize(left.row, right.row, left.column, right.column);
	resizeMatrix(left, normalizedMatrixSize, normalizedMatrixSize);
	resizeMatrix(right, normalizedMatrixSize, normalizedMatrixSize);

	COMPLEX_MATRIX* d, * d1, * d2, * h1, * h2, * v1, * v2;
	d = new COMPLEX_MATRIX;
	d1 = new COMPLEX_MATRIX;
	d2 = new COMPLEX_MATRIX;
	h1 = new COMPLEX_MATRIX;
	h2 = new COMPLEX_MATRIX;
	v1 = new COMPLEX_MATRIX;
	v2 = new COMPLEX_MATRIX;
	createZeroMatrix(*d, normalizedMatrixSize / 2, normalizedMatrixSize / 2);
	createZeroMatrix(*d1, normalizedMatrixSize / 2, normalizedMatrixSize / 2);
	createZeroMatrix(*d2, normalizedMatrixSize / 2, normalizedMatrixSize / 2);
	createZeroMatrix(*h1, normalizedMatrixSize / 2, normalizedMatrixSize / 2);
	createZeroMatrix(*h2, normalizedMatrixSize / 2, normalizedMatrixSize / 2);
	createZeroMatrix(*v1, normalizedMatrixSize / 2, normalizedMatrixSize / 2);
	createZeroMatrix(*v2, normalizedMatrixSize / 2, normalizedMatrixSize / 2);

	for (int i = 0; i < normalizedMatrixSize / 2; i++)
	{
		for (int j = 0; j < normalizedMatrixSize / 2; j++)
		{
			for (int z = 0; z < normalizedMatrixSize / 2; z++)
			{
				_complex leftMatrixFirstQuarter = left.matrix[i][z + normalizedMatrixSize / 2];
				_complex leftMatrixSecondQuarter = left.matrix[i][z];
				_complex leftMatrixThirdQuarter = left.matrix[i + normalizedMatrixSize / 2][z];
				_complex leftMatrixFourthQuarter = left.matrix[i + normalizedMatrixSize / 2][z + normalizedMatrixSize / 2];
				_complex rightMatrixFirstQuarter = right.matrix[z][j + normalizedMatrixSize / 2];
				_complex rightMatrixSecondQuarter = right.matrix[z][j];
				_complex rightMatrixThirdQuarter = right.matrix[z + normalizedMatrixSize / 2][j];
				_complex rightMatrixFourthQuarter = right.matrix[z + normalizedMatrixSize / 2][j + normalizedMatrixSize / 2];

				d->matrix[i][j] += (leftMatrixSecondQuarter + leftMatrixFourthQuarter) * (rightMatrixSecondQuarter + rightMatrixFourthQuarter);
				d1->matrix[i][j] += (leftMatrixFirstQuarter - leftMatrixFourthQuarter) * (rightMatrixThirdQuarter + rightMatrixFourthQuarter);
				d2->matrix[i][j] += (leftMatrixThirdQuarter - leftMatrixSecondQuarter) * (rightMatrixSecondQuarter + rightMatrixFirstQuarter);
				h2->matrix[i][j] += (leftMatrixThirdQuarter + leftMatrixFourthQuarter) * rightMatrixSecondQuarter;
				h1->matrix[i][j] += (leftMatrixSecondQuarter + leftMatrixFirstQuarter) * rightMatrixFourthQuarter;
				v1->matrix[i][j] += leftMatrixSecondQuarter * (rightMatrixFirstQuarter - rightMatrixFourthQuarter);
				v2->matrix[i][j] += leftMatrixFourthQuarter * (rightMatrixThirdQuarter - rightMatrixSecondQuarter);
			}
		}
	}
	COMPLEX_MATRIX resultMatrix;
	createZeroMatrix(resultMatrix, normalizedMatrixSize, normalizedMatrixSize);

	for (int i = 0; i < normalizedMatrixSize / 2; i++)
	{
		for (int j = 0; j < normalizedMatrixSize / 2; j++)
		{
			resultMatrix.matrix[i][j] = d->matrix[i][j] + v2->matrix[i][j] - h1->matrix[i][j] + d1->matrix[i][j];
			resultMatrix.matrix[i][j + normalizedMatrixSize / 2] = v1->matrix[i][j] + h1->matrix[i][j];
			resultMatrix.matrix[i + normalizedMatrixSize / 2][j] = h2->matrix[i][j] + v2->matrix[i][j];
			resultMatrix.matrix[i + normalizedMatrixSize / 2][j + normalizedMatrixSize / 2] = d->matrix[i][j] - h2->matrix[i][j] + v1->matrix[i][j] + d2->matrix[i][j];
		}
	}
	delete d, d1, d2, h1, h2, v1, v2;
	return resultMatrix;
}

void createZeroMatrix(COMPLEX_MATRIX& matrix, const int& row, const int& col)
{
	matrix.row = row;
	matrix.column = col;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix.matrix[i][j] = { 0.0, 0.0 };
		}
	}
}

COMPLEX_MATRIX createIdentityMatrix(const int& row, const int& col)
{
	COMPLEX_MATRIX matrix;
	matrix.row = row;
	matrix.column = col;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i == j) {
				matrix.matrix[i][j] = { 1.0, 0.0 };
			}
			else {
				matrix.matrix[i][j] = { 0.0, 0.0 };
			}
		}
	}
	return matrix;
}

COMPLEX_MATRIX* getRange(COMPLEX_MATRIX* matrixes, int start, int count) {
	COMPLEX_MATRIX* part = new COMPLEX_MATRIX[count];
	for (int i = 0; i < count; i++) {
		part[i] = matrixes[i + start];
	}
	return part;
}

void printMatrix(COMPLEX_MATRIX* matrix) {
	for (int i = 0; i < matrix->row; i++) {
		for (int j = 0; j < matrix->column; j++) {
			std::cout << "{ " << matrix->matrix[i][j].x << "; " << matrix->matrix[i][j].y << " }\t";
		}
		std::cout << std::endl;
	}
}

_complex operator+(const _complex left, const _complex right)
{
	_complex result = { left.x + right.x, left.y + right.y };
	return result;
}

_complex operator-(const _complex left, const _complex right) {
	_complex result = { left.x - right.x, left.y - right.y };
	return result;
}

_complex operator*(const _complex left, const _complex right) {
	_complex result = { left.x * right.x - left.y * right.y, left.x * right.y + left.y * right.x };
	return result;
}

_complex operator+=(_complex& left, const _complex right) {
	left = left + right;
	return left;
}
