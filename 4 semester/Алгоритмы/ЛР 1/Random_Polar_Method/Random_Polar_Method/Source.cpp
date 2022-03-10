#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

int RandomPolar()
{
	double u1;
	double u2;
	double v1;
	double v2;
	double s;
	while (true)
	{
		u1 = rand() / INT_MAX;
		u2 = rand() / INT_MAX;
		v1 = 2 * u1 - 1;
		v2 = 2 * u2 - 1;

		s = v1 * v1 + v2 * v2;
		if (s < 1)
			break;
	}

	double n1, n2;
	n1 = v1 * sqrt(-2 * log(s) / s);
	n2 = v2 * sqrt(-2 * log(s) / s);
	return n1;

}
int main()
{
	time_t k;
	srand((unsigned)(&k));
	std::vector<double> arr;

	double u1;
	double u2;
	double v1;
	double v2;
	double s;
	int i = 0;
	while (i < 10)
	{
		while (true)
		{
			u1 = double(rand()) / 32767;
			u2 = double(rand()) / 32767;
			v1 = 2.0 * u1 - 1;
			v2 = 2.0 * u2 - 1;

			s = v1 * v1 + v2 * v2;
			if (s < 1)
				break;
		}

		double n1, n2;
		n1 = v1 * sqrt(-2 * log(s) / s);
		n2 = v2 * sqrt(-2 * log(s) / s);
		arr.push_back(n1);
		arr.push_back(n2);
		i++;
	}
	i = 0;

	/*std::ofstream fout2("2.txt");
	while (i < 20)
	{
		i++;
		fout2 << i << '\n';
	}
	fout2.close();*/
	
	std::sort(arr.begin(), arr.end());

	std::ofstream fout("1.txt");
	for (double i : arr)
	{
		fout << i << "\n";
	}
	fout.close();


}