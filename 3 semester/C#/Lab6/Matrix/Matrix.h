#pragma once

#ifndef MATRIX_EXPORTS
	#define MATRIX_API __declspec(dllexport)
#else
	#define MATRIX_API __declspec(dllimport)
#endif // !MATRIX_EXPORTS


class TridiagonalMatrix
{
private:
	int dimension;
	double* mainDiag;
	double* belowMainDiag;
	double* aboveMainDiag;
public:
	TridiagonalMatrix(int _dim = 2);
	TridiagonalMatrix(int _dim, double* _diag);
	TridiagonalMatrix(const TridiagonalMatrix& _matrix);
	~TridiagonalMatrix();

	double* Solve(double* _f);

	TridiagonalMatrix& operator=(const TridiagonalMatrix& _matrix);
};

extern "C" MATRIX_API double matrixInit(int dimension, int count);

extern "C" MATRIX_API double* matrixSolve(int dimension, double* _diag, double* _f);