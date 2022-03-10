#include "Matrix.h"
#include <exception>
#include <chrono>
#include <iostream>

TridiagonalMatrix::TridiagonalMatrix(int _dim)
{
	dimension = _dim;
	line = new double[_dim];
	column = new double[_dim];
	for (int i = 0; i < dimension ; i++)
	{
		line[i] = i+1;
	}
	for (int i = dimension-1; i >= 0; i--)
	{
		column[i] = i+1;
	}
}


TridiagonalMatrix::TridiagonalMatrix(int _dim, double* _diag)
{
	if (_dim < 2)
		throw std::exception("Dimension must be greater than 2");
	dimension = _dim;
	line = new double[_dim];
	for (int i = 0; i < _dim; i++)
	{
		line[i] = _diag[i];
	}
	column = new double[_dim];
	for (int i = _dim; i < _dim * 2; i++)
	{
		column[i - _dim] = _diag[i];
	}
}

TridiagonalMatrix::TridiagonalMatrix(const TridiagonalMatrix& _matrix)
{
	dimension = _matrix.dimension;
	line = new double[dimension];
	column = new double[dimension];
	for (int i = 0; i < dimension ; i++)
	{
		line[i] = _matrix.line[i];
	}
	for (int i = 0; i < dimension; i++)
	{
		column[i] = _matrix.column[i];
	}
}

TridiagonalMatrix::~TridiagonalMatrix()
{
	delete[] line;
	delete[] column;
}

double* TridiagonalMatrix::Solve(double* _f)
{
	/*double *x, *y, F=0, G=0, r=0, s=0, t = 0;
	double* solve, *x_tmp, *y_tmp, **A_1, **A_2;
	int k = 1;
	x = new double[dimension];
	y = new double[dimension];
	x_tmp = new double[dimension];
	y_tmp = new double[dimension];

	x[0] = 1.0 / line[0];
	y[0] = 1.0 / line[0];

	for (k = 1; k < dimension;)
	{
		F = 0;
		G = 0;
		r = 0;
		s = 0;
		t = 0;

		for (int i = 00; i < k; i++)
		{
			F += line[dimension - 1 - i] * x[i];
			G += column[i+1] * y[i];
		}
		r = 1.0 / (1 - F * G);
		s = r * F  *(-1);
		t = r * G * (-1);

		k++;
		for (int i = 0; i < k - 1; i++)
		{
			x_tmp[i] = x[i];
			y_tmp[i] = y[i];
		}
		x[0] = x[0] * r;
		x[k - 1] = y_tmp[k - 2] * s;
		for (int i = 1; i < k - 2; i++)
			x[i] += x_tmp[i] * r + y_tmp[i] * s;

		y[0] = x_tmp[0] * t;
		y[k - 1] = y_tmp[k - 2] * r;
		for (int i = 1; i < k - 2; i++)
			y[i] += x_tmp[i] * t + y_tmp[i] * r;
	}

	A_1 = new double*[k];
	for (int i = 0; i < k; i++)
		A_1[i] = new double[k];

	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
		{
			A_1[i][j] = x[i] * y[k - 1 - j];
			if (j >= i && i > 0)
				A_1[i][j] += A_1[i - 1][j - 1];
		}

	A_2 = new double*[k];
	for (int i = 0; i < k; i++)
		A_2[i] = new double[k];
	for (int i = 0; i < k; i++)
	{
		A_2[0][i] = 0;
		A_2[i][0] = 0;
	}

	for (int i = 1; i < k; i++)
		for (int j = 1; j < k; j++)
		{
			A_2[i][j] = y[i-1] * x[k - j];
			if (j >= i && i > 1)
				A_2[i][j] += A_1[i - 1][j - 1];
		}
	
	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
		{
			A_1[i][j] -= A_2[i][j];
			A_1[i][j] /= x[0];
		}

	solve = new double[k];

	for (int i = 0; i < k; i++)
	{
		solve[i] = A_1[i][0] * _f[i];
		for (int j = 1; j < k; j++)
			solve[i] += A_1[i][j] * _f[j];
	}
	
	delete[] x;
	delete[] y;
	for (int i = 0; i < dimension; i++)
	{
		delete[] A_2[i];
		delete[] A_1[i];
	}
	delete[] A_1;
	delete[] A_2;

	return solve;*/
	
bool flag = true;
double *lc = new double[2 * dimension - 1];
double **a, *ans = new double[dimension];
int n = dimension;
int m = dimension;
const double EPS = 0.001;

for (int i = 0; i < dimension; i++)
	lc[i] = line[i];
for (int i = 1; i < dimension; i++)
	lc[dimension - 1 + i] = column[i];

a = new double*[dimension];
for (int i = 0; i < dimension; i++)
{
	a[i] = new double[dimension + 1];
}

for (int i = 0; i < dimension; i++)
{
	for (int j = 0; j < dimension; j++)
	{
		a[i][j] = lc[dimension - 1 + j - i];
	}
	a[i][dimension] = _f[i];
}
int  *where = new int[m];
for (int i = 0; i < m; i++)
	where[i] = -1;

for (int col = 0, row = 0; col < m && row < n; ++col) {
	int sel = row;
	for (int i = row; i < n; ++i)
		if (abs(a[i][col]) > abs(a[sel][col]))
			sel = i;
	if (abs(a[sel][col]) < EPS)
		continue;
	for (int i = col; i <= m; ++i)
		std::swap(a[sel][i], a[row][i]);
	where[col] = row;

	for (int i = 0; i < n; ++i)
		if (i != row) {
			double c = a[i][col] / a[row][col];
			for (int j = col; j <= m; ++j)
				a[i][j] -= a[row][j] * c;
		}
	++row;
}

for (int i = 0; i < m; i++)
	ans[i] = 0;
for (int i = 0; i < m; ++i)
	if (where[i] != -1)
		ans[i] = a[where[i]][m] / a[where[i]][i];
for (int i = 0; i < n; ++i) {
	double sum = 0;
	for (int j = 0; j < m; ++j)
		sum += ans[j] * a[i][j];
	if (abs(sum - a[i][m]) > EPS)
		return 0;
}

return ans;
}

TridiagonalMatrix& TridiagonalMatrix::operator=(const TridiagonalMatrix& _matrix)
{
	dimension = _matrix.dimension;
	line = new double[dimension];
	column = new double[dimension];
	for (int i = 0; i < dimension; i++)
	{
		line[i] = _matrix.line[i];
	}
	for (int i = 0; i < dimension; i++)
	{
		column[i] = _matrix.column[i];
	}
	return *this;
}

//double matrixInit(int dimension, int count)
//{
//	using clock_t = std::chrono::high_resolution_clock;
//	using second_t = std::chrono::duration< double, std::ratio <1> >;
//
//	TridiagonalMatrix matr(dimension);
//	double* f = new double[dimension];
//	std::chrono::time_point<clock_t> beg = clock_t::now();
//	for (int i = 0; i < dimension; i++)
//	{
//		f[i] = dimension;
//	}
//
//	beg = clock_t::now();
//	for (int i = 0; i < count; ++i)
//		matr.Solve(f);
//	return std::chrono::duration_cast<second_t>(clock_t::now() - beg).count();
//}
//
//
//double* matrixSolve(int dimension, double* _diag, double* _f)
//{
//	TridiagonalMatrix matr(dimension, _diag);
//	double* solution;
//	solution = matr.Solve(_f);
//	for (int i = 0; i < dimension; i++)
//		std::cout << solution[i] << " " << std::endl;
//	return solution;
//}
