#include <iostream>
#include <chrono>
#include <vector>


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

void BinaryInsertionSort(std::vector<int> *arr)
{
	int buff;
	int middle = 0;
	int left;
	int right;
	Timer t;
	for (int i = 1; i < (*arr).size(); i++)
	{
		left = -1;
		right = i;
		while (left < right - 1)
		{
			middle = (left + right) / 2;
			if ((*arr)[i] > (*arr)[middle])
				left = middle;
			else
				right = middle;
		}
		for (int j = i; j > right; j--)
		{
			buff = (*arr)[j];
			(*arr)[j] = (*arr)[j-1];
			(*arr)[j-1] = buff;
		}
	}
	std::cout << t.elapsed() << std::endl;
}

int main()
{
	srand(1597);
	std::vector<int> arr;
	for (int i = 0; i < 8500; i++)
		arr.push_back(rand());
	BinaryInsertionSort(&arr);


	/*for (int i : arr)
		std::cout << i << " ";*/
	return 0;
}