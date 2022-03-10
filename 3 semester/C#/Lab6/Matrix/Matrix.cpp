#include "pch.h"
#include "Matrix.h"
#include <exception>
#include <chrono>
#include <iostream>

TridiagonalMatrix::TridiagonalMatrix(int _dim)
	{
		dimension = _dim;
		mainDiag = new double[_dim];
		belowMainDiag = new double[_dim - 1];
		aboveMainDiag = new double[_dim - 1];
		for (int i = 0; i < dimension; i++)
		{
			mainDiag[i] = i;
		}
		for (int i = 0; i < dimension - 1; i++)
		{
			aboveMainDiag[i] = i;
			belowMainDiag[i] = i;
		}
	}

TridiagonalMatrix::TridiagonalMatrix(int _dim, double* _diag)
	{
		if (_dim < 2)
			throw std::exception("Dimension must be greater than 2");
		dimension = _dim;
		aboveMainDiag = new double[_dim - 1];
		for (int i = 0; i < _dim - 1; i++)
		{
			aboveMainDiag[i] = _diag[i];
		}
		mainDiag = new double[_dim];
		for (int i = _dim - 1; i < _dim * 2 - 1; i++)
		{
			mainDiag[i - _dim + 1] = _diag[i];
		}
		belowMainDiag = new double[_dim - 1];
		for (int i = _dim * 2 - 1; i < _dim * 3 - 2; i++)
		{
			belowMainDiag[i - _dim * 2 + 1] = _diag[i];
		}
	}

TridiagonalMatrix::TridiagonalMatrix(const TridiagonalMatrix& _matrix)
	{
		dimension = _matrix.dimension;
		mainDiag = new double[dimension];
		aboveMainDiag = new double[dimension - 1];
		belowMainDiag = new double[dimension - 1];
		for (int i = 0; i < dimension - 1; i++)
		{
			aboveMainDiag[i] = _matrix.aboveMainDiag[i];
		}
		for (int i = 0; i < dimension; i++)
		{
			mainDiag[i] = _matrix.mainDiag[i];
		}
		for (int i = 0; i < dimension - 1; i++)
		{
			belowMainDiag[i] = _matrix.belowMainDiag[i];
		}
	}

TridiagonalMatrix::~TridiagonalMatrix()
	{
		delete[] mainDiag;
		delete[] aboveMainDiag;
		delete[] belowMainDiag;
	}

	double* TridiagonalMatrix::Solve(double* _f)
	{
		double* beta = new double[dimension];
		double* gamma = new double[dimension];

		beta[0] = (aboveMainDiag[0] / mainDiag[0]);
		gamma[0] = (_f[0] / mainDiag[0]);

		for (int i = 1; i < dimension - 1; i++)
		{
			beta[i] = (aboveMainDiag[i] / (mainDiag[i] - beta[i - 1] * belowMainDiag[i - 1]));
			gamma[i] = ((_f[i] - belowMainDiag[i - 1] * gamma[i - 1]) / (mainDiag[i] - beta[i - 1] * belowMainDiag[i - 1]));
		}
		gamma[dimension - 1] = ((_f[dimension - 1] - belowMainDiag[dimension - 2] * gamma[dimension - 2]) / (mainDiag[dimension - 1] - beta[dimension - 2] * belowMainDiag[dimension - 2]));

		double* solve = new double[dimension];
		solve[dimension - 1] = gamma[dimension - 1];
		for (int i = dimension - 2; i >= 0; i--)
		{
			solve[i] = gamma[i] - beta[i] * solve[i + 1];
		}

		delete[] beta;
		delete[] gamma;

		return solve;
	}

	TridiagonalMatrix& TridiagonalMatrix::operator=(const TridiagonalMatrix& _matrix)
	{
		dimension = _matrix.dimension;
		mainDiag = new double[dimension];
		aboveMainDiag = new double[dimension - 1];
		belowMainDiag = new double[dimension - 1];
		for (int i = 0; i < dimension - 1; i++)
		{
			aboveMainDiag[i] = _matrix.aboveMainDiag[i];
		}
		for (int i = 0; i < dimension; i++)
		{
			mainDiag[i] = _matrix.mainDiag[i];
		}
		for (int i = 0; i < dimension - 1; i++)
		{
			belowMainDiag[i] = _matrix.belowMainDiag[i];
		}
		return *this;
	}

__declspec(dllexport) double matrixInit( int dimension, int count)
{
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration< double, std::ratio <1> >;

	TridiagonalMatrix matr(dimension);
	double* f = new double[dimension];
	std::chrono::time_point<clock_t> beg = clock_t::now();
	for (int i = 0; i < dimension; i++)
	{
		f[i] = dimension;
	}
	
	beg = clock_t::now();
	for (int i = 0; i < count; ++i)
		matr.Solve(f);
	return std::chrono::duration_cast<second_t>(clock_t::now() - beg).count();
}


double* matrixSolve(int dimension, double* _diag, double* _f)
{
	TridiagonalMatrix matr(dimension, _diag);
	double* solution;
	solution = matr.Solve(_f);
	for (int i = 0; i < dimension; i++)
		std::cout << solution[i] << " " << std::endl;
	return solution;
}
