#include <iostream>
#include <vector>
#include <chrono>

class Timer
{
public:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration< double, std::ratio <1> >;

private:
	std::chrono::time_point<clock_t> beg;
public:

	Timer()
	{
		beg = clock_t::now();
	}

	double elapsed()
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - beg).count();
	}

	double resset()
	{
		beg = clock_t::now();
	}
};

void shaker_sort(std::vector<int> *arr)
{
	int buff;
	int control = (*arr).size();
	int left = 0;
	int right = (*arr).size() - 1;
	Timer timer;
	do
	{
		for (int i = left; i < right; i++)
		{
			if ((*arr)[i] > (*arr)[i + 1])
			{
				buff = (*arr)[i];
				(*arr)[i] = (*arr)[i + 1];
				(*arr)[i + 1] = buff;
				control = i;
			}
		}
		right = control;
		for (int i = right; i > left; i--)
		{
			if ((*arr)[i] < (*arr)[i - 1])
			{
				buff = (*arr)[i];
				(*arr)[i] = (*arr)[i - 1];
				(*arr)[i - 1] = buff;
				control = i;
			}
		}
		left = control;
	} while (left < right);
	std::cout << timer.elapsed() << std::endl;
}

int main()
{
	srand(1597);
	std::vector<int> arr;
	for (int i = 0; i < 8500; i++)
		arr.push_back(rand());
	shaker_sort(&arr);

	/*for (int i : arr)
	{
		std::cout << i << " ";
	}*/
	return 0;
}