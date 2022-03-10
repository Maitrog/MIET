#include <iostream>
#include <vector>

bool FibonacciSearch(std::vector<int> *arr, int begin, int end, int key)
{
	int prev = 1;
	int now = 2;
	int next = 3;
	if (end - begin == 1)
	{
		if (((*arr)[begin + prev - 1] == key || (*arr)[begin + now - 1] == key))
			return true;
		else
			return false;
	}
	if ((*arr)[begin + prev - 1] > key)
		return false;
	for (int i = begin; i < end;)
	{
		if ((*arr)[begin + prev - 1] <= key && (*arr)[begin + now - 1] >= key)
		{
			if (FibonacciSearch(arr, begin + prev - 1, begin + now - 1, key))
				return true;
			break;
		}
		else
		{
			prev = now;
			now = (begin + next) > arr->size()?arr->size() - begin:next;
			next = prev + now;
			i = now - 1;
		}
	}
	return false;
}

int main()
{
	std::vector<int> arr1{ 3, 5, 8, 9, 11, 14, 15, 19, 21, 22, 28, 33, 35, 37, 42, 45, 48, 52 };
	for(int i = 0; i < 53;i++)
	if (FibonacciSearch(&arr1, 0, arr1.size(), i))
		std::cout << i << " OK" << std::endl;
	else
		std::cout<< i << " GG" << std::endl;
	return 0;
}