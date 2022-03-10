#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <complex>
#include "Matrix.h"

#define PI 3.141592

double* matrixSolve(int dimension, double* _diag, double* _f)
{
	TridiagonalMatrix matr(dimension, _diag);
	double* solution;
	solution = matr.Solve(_f);
	for (int i = 0; i < dimension; i++)
		std::cout << solution[i] << " " << std::endl;
	return solution;
}

double matrixInit(int dimension, int count)
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

	delete[] f;

	return std::chrono::duration_cast<second_t>(clock_t::now() - beg).count();
}

int gauss(std::vector < std::vector<double> > a, std::vector<double> & ans) {
	int n = (int)a.size();
	int m = (int)a[0].size() - 1;
	const int INF = 100000007;
	const double EPS = 0.001;

	std::vector<int> where(m, -1);
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

	ans.assign(m, 0);
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

	for (int i = 0; i < m; ++i)
		if (where[i] == -1)
			return INF;
	return 1;
}
int main()
{
	double* s = new double[4]{1,2,2,3 };
	double* f = new double[2]{ 2,2};
	//std::vector < std::vector<double> > a{ {1,2,3,2},{2,3,4,2},{3,4,5,2}};
	//std::vector<double> ans{2,2,2};
	//gauss(a, ans);
	//TridiagonalMatrix m(2, s);
	matrixSolve(2, s, f);
	//std::cout << matrixInit(10000, 1);

	delete[] s;
	delete[] f;
}