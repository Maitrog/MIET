#pragma once
class TridiagonalMatrix
{
private:
	int dimension;
	double* line;
	double* column;
public:
	TridiagonalMatrix(int _dim = 2);
	TridiagonalMatrix(int _dim, double* _diag);
	TridiagonalMatrix(const TridiagonalMatrix& _matrix);
	~TridiagonalMatrix();

	double* Solve(double* _f);

	TridiagonalMatrix& operator=(const TridiagonalMatrix& _matrix);
};

//double matrixInit(int dimension, int count);
//
//double* matrixSolve(int dimension, double* _diag, double* _f);