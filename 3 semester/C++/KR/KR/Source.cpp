#include <iostream>
#include "Vector.h"


int main()
{
	try {
		int arr[] = { 1,2,3,5,4,6 };
		int arr2[] = { 6,4,2,5,1,3 };

		Vector vec(6, arr);
		Vector vec2(6, arr2);
		std::cout << vec;
		std::cout << vec2;

		vec++;
		vec2--;
		std::cout << vec;
		std::cout << vec2;

		vec = vec * vec2;
		vec2 = -vec2;
		std::cout << vec;
		std::cout << vec2;

		std::cin >> vec2;
		std::cout << vec2;

		if (vec > vec2)
			std::cout << "vec" << std::endl;
		else
			std::cout << "vec2" << std::endl;

		if (vec < vec2)
			std::cout << "vec" << std::endl;
		else
			std::cout << "vec2" << std::endl;

	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	return 0;
}