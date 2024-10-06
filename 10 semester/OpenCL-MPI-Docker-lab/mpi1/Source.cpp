#define	_CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include "mpi.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>


double f(double x)
{
	return 1 / (1 + x * x);
}

//Формула средних прямоугольников
int midpoint_quadrature_rule(int myrank, int nprocs, int pows)
{
	double pi_value = M_PI;

	double pi, sum = 0, term, h, n = pow(2, pows);
	int i;

	double start = MPI_Wtime();

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	h = 1.0 / n;
	for (i = myrank + 1; i <= n; i += nprocs)
	{
		sum += f(h * (i - 0.5));
	}
	term = 4 * h * sum;
	MPI_Reduce(&term, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	double end = MPI_Wtime();
	double mpi_time = (end - start) * 1000;
	if (myrank == 0)
	{
		printf("Values of n, time, M_PI - pi:\t|\t2^%d\t|\t%f ns.\t|\t%lg\t|\n\n", pows, mpi_time, pi_value - pi);
	}

	//MPI_Finalize();
	return 0;
}

//Формула трапеций
int trapezium_quadrature_rule(int myrank, int nprocs, int pows)
{
	double pi_value = double(M_PI);

	double pi, sum = 0, term, h, n = pow(2, pows);
	int i;

	double start = MPI_Wtime();

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	h = 1.0 / n;
	for (i = myrank + 1; i <= n - 1; i += nprocs)
	{
		sum += f(0 + i * h);
	}
	term = 4 * h * sum;
	MPI_Reduce(&term, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	pi += ((f(0) + f(1)) / 2) * h * 4;

	double end = MPI_Wtime();
	double mpi_time = (end - start) * 1000;
	if (myrank == 0)
	{
		printf("Values of n, time, M_PI - pi:\t|\t2^%d\t|\t%f ns.\t|\t%lg\t|\n\n ", pows, mpi_time, pi_value - pi);
	}

	//MPI_Finalize();
	return 0;
}

//Формула Симпсона
//int simpson_quadrature_rule(int argc, char* argv[], int n)
int simpson_quadrature_rule(int myrank, int nprocs, int pows)
{

	double pi_value = double(M_PI);

	double pi, sum1 = 0, sum2 = 0, term, h, n = pow(2, pows);
	int i;

	double start = MPI_Wtime();

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	h = 1.0 / n;
	for (i = myrank + 1; i <= n; i += nprocs)
	{
		sum1 += 2 * f(h * (i - 0.5));
	}
	for (i = myrank + 1; i <= n - 1; i += nprocs)
	{
		sum2 += f((0 + i * h));
	}
	term = 4 * h / 3 * (sum1 + sum2);
	MPI_Reduce(&term, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	pi += ((f(0) + f(1)) / 2) * h * 4 / 3;

	double end = MPI_Wtime();
	double mpi_time = (end - start) * 1000;
	if (myrank == 0)
	{
		printf("Values of n, time, M_PI - pi:\t|\t2^%d\t|\t%f ns.\t|\t%lg\t|\n\n", pows, mpi_time, pi_value - pi);
	}

	//MPI_Finalize();
	return 0;
}

int n_cycles(int(*func_ptr)(int, int, int), int myrank, int nproc)
{
	int result = 0;
	for (int iter = 8; iter <= 15; iter++) { result = func_ptr(myrank, nproc, iter); }

	return result;
}

int main(int argc, char* argv[])
{
	int it_number;
	//printf("Number of iterations = ");
	//scanf("%d", &it_number);

	int myrank, nprocs;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	if (myrank == 0 ) printf("\t1. MIDPOINT_QUADRATURE_RULE:\n\n");
	//midpoint_quadrature_rule(myrank, nprocs, it_number);
	n_cycles(&midpoint_quadrature_rule, myrank, nprocs);

	if (myrank == 0) printf("\t2. TRAPEZIUM_QUADRATURE_RULE:\n\n");
	//trapezium_quadrature_rule(myrank, nprocs, it_number);
	n_cycles(&trapezium_quadrature_rule, myrank, nprocs);

	if (myrank == 0) printf("\t3. SIMPSON_QUADRATURE_RULE:\n\n");
	//simpson_quadrature_rule(myrank, nprocs, it_number);
	n_cycles(&simpson_quadrature_rule, myrank, nprocs);

	MPI_Finalize();
	return 0;
}