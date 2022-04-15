#include <iostream>
#include <cstdlib>
#include <cmath>
#include <mpi.h>
#include <cstddef>
#include <complex.h>
#include <cmath>

constexpr int MAX_SIZE = 4;
constexpr int MATRIX_NUMBERS = 4;
constexpr int SIZE = 2;

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
void TestComm(MPI_Comm* multiplyComm, int i, int rank, int size);
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

int main(int argc, char** argv) {

	MPI_Init(&argc, &argv);

	int rank, size;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	COMPLEX_MATRIX* matrixes = new COMPLEX_MATRIX[0];
	COMPLEX_MATRIX* fromRoot = new COMPLEX_MATRIX[0];
	int* matrixCount = new int[size - 1];
	MPI_Status Status;
	COMPLEX_MATRIX localResult;

	srand(rank * 10);

#pragma region InitializeMatrix

	int matrixNumbers = MATRIX_NUMBERS > (size - 1) * 2 ? MATRIX_NUMBERS : (size - 1) * 2;
	if (rank == 0) {
		getchar();
		//delete[] matrixes;
		matrixes = new COMPLEX_MATRIX[matrixNumbers];
		for (int i = 0; i < MATRIX_NUMBERS; i++) {
			matrixes[i] = createMatrix(SIZE, SIZE);
		}
		for (int i = MATRIX_NUMBERS; i < (size - 1) * 2; i++) {
			matrixes[i] = createIdentityMatrix(SIZE, SIZE);
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

#pragma region CreateGroupAndCommunicator

	int multiplyGroupSize = ((double)size / 2 + 1) / 2.0 * (size / 2);
	MPI_Group worldGroup;
	MPI_Group* multiplyGroup = new MPI_Group[multiplyGroupSize];
	MPI_Comm* multiplyComm = new MPI_Comm[multiplyGroupSize];
	//MPI_Group multiplyGroup[3];
	//MPI_Comm multiplyComm[3];
	MPI_Comm_group(MPI_COMM_WORLD, &worldGroup);

	for (int i = 1, number = 0; i < size; i *= 2) {
		for (int j = 1; j < size; j += 2 * i) {
			int n;
			int* ranks = new int[0];
			if (size - j > i) {
				//delete[] ranks;
				n = 2;
				ranks = new int[n] { j, j + i };
			}
			else {
				//delete[] ranks;
				n = 1;
				ranks = new int[1]{ j };
			}
			MPI_Group_incl(worldGroup, n, ranks, &(multiplyGroup[number]));
			//delete[] ranks;
			number++;
		}
	}

	for (int i = 0; i < multiplyGroupSize; i++) {
		MPI_Comm_create(MPI_COMM_WORLD, multiplyGroup[i], &(multiplyComm[i]));
		
		TestComm(multiplyComm, i, rank, size);
	}

#pragma endregion

#pragma region FirstLayer

	int procesLeft = size - 1;
	int matrixLeft = matrixNumbers;
	/*if (multiplyComm[0] != MPI_COMM_NULL) {
		MPI_Barrier(multiplyComm[0]);
	}*/
	for (int i = 1; i < size; i++) {
		matrixCount[i - 1] = round((double)matrixLeft / procesLeft);
		if (rank == 0) {
			COMPLEX_MATRIX* partOfMatrixes = getRange(matrixes, matrixNumbers - matrixLeft, matrixCount[i - 1]);
			MPI_Send(partOfMatrixes, matrixCount[i - 1], custom_dt, i, 0, MPI_COMM_WORLD);
			//delete[] partOfMatrixes;
		}
		procesLeft--;
		matrixLeft -= matrixCount[i - 1];
	}
	/*if (multiplyComm[0] != MPI_COMM_NULL) {
		MPI_Barrier(multiplyComm[0]);
	}*/
	if (rank != 0) {
		MPI_Recv(fromRoot, matrixCount[rank - 1], custom_dt, 0, 0, MPI_COMM_WORLD, &Status);
		printf("global rank: %d\n", rank);
		localResult = fromRoot[0];
		for (int i = 1; i < matrixCount[rank - 1]; i++) {
			localResult = Multiply(localResult, fromRoot[i]);
		}
	}
	/*if (multiplyComm[0] != MPI_COMM_NULL) {
		MPI_Barrier(multiplyComm[0]);
	}*/

#pragma endregion

#pragma region OtherLayers

	if (rank != 0)
	{
		for (int i = 0; i < multiplyGroupSize; i++) {
			printf("comm2: %d\n", multiplyComm[i]);
			if (MPI_COMM_NULL != multiplyComm[i]) {

				//if (size % 2 == 0 && i + 1 == multiplyGroupSize)
				//{

				//}
				int prime_rank = -1;
				//MPI_Comm_rank(multiplyComm[i], &prime_rank);
				MPI_Gather(&localResult, 1, custom_dt, fromRoot, 2, custom_dt, 0, multiplyComm[i]);
				if (prime_rank == 0)
				{
					localResult = Multiply(fromRoot[0], fromRoot[1]);
					printMatrix(&localResult);
				}
			}
		}
	}

#pragma endregion

	if (rank == 1) {
		MPI_Send(&localResult, 1, custom_dt, 0, 0, MPI_COMM_WORLD);
	}
	else if (rank == 0) {
		MPI_Recv(fromRoot, 1, custom_dt, 1, 0, MPI_COMM_WORLD, &Status);
		printMatrix(fromRoot);
	}


#pragma region FreeGroupAndCommunicator

	/*for (int i = 0; i < multiplyGroupSize; i++) {
		if (MPI_COMM_NULL != multiplyComm[i]) {
			MPI_Group_free(&(multiplyGroup[i]));
			MPI_Comm_free(&(multiplyComm[i]));
		}
	}*/

#pragma endregion

	MPI_Finalize();
	//delete[] matrixes, fromRoot, matrixCount, multiplyGroup, multiplyComm;
	return 0;
}

void TestComm(MPI_Comm* multiplyComm, int i, int rank, int size)
{
	int prime_rank = -1, prime_size = -1;
	printf("comm: %d\n", multiplyComm[i]);
	if (MPI_COMM_NULL != multiplyComm[i]) {
		MPI_Comm_rank(multiplyComm[i], &prime_rank);
		MPI_Comm_size(multiplyComm[i], &prime_size);
	}
	printf("WORLD RANK/SIZE: %d/%d \t PRIME RANK/SIZE: %d/%d\n",
		rank, size, prime_rank, prime_size);
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
	//delete[] d, d1, d2, h1, h2, v1, v2;
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
			matrix.matrix[i][j] = { 1.0, 0.0 };
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
