#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Vector22.h"
#include "ZeroDivisionException.h"
#include "DiscrepancySizeException.h"
#include "IndexOutOfRangeException.h"
#include "WrongSizeException.h"
#include "NullPtrException.h"



	
	Vector22::Vector22(int _size, int* _array)
	{
		if (_array == nullptr)
			throw NullPtrException();
		if (_size < 0)
			throw WrongSizeException();
		size = _size;
		array = new int[_size];
		for (int i = 0; i < size; i++)
			*(array + i) = *(_array + i);
	}
	Vector22::Vector22() :Vector22(0, nullptr)
	{

	}
	Vector22::~Vector22()
	{
		delete[] array;
		std::cout << "Object destroyed" << std::endl;
	}
	int Vector22::getSize()
	{
		return size;
	}

	Vector22& Vector22::operator =(Vector22& vec1) {
		if (vec1.array == nullptr)
			throw NullPtrException();
		if (this == &vec1) {
			return *this;
		}
		array = new int[vec1.size];
		size = vec1.size;
		for (int i = 0; i < size; i++) {
			array[i] = vec1.array[i];
		}

		return *this;
	}



	Vector22& operator +(Vector22& vec1, Vector22& vec2) {
		if (vec1.size != vec2.size)
			throw DiscrepancySizeException(vec1.size, vec2.size);
		if (vec1.array == nullptr || vec2.array == nullptr)
			throw NullPtrException();
		Vector22* Sumvec = new Vector22(vec1.size, vec1.array);
		for (int i = 0; i < vec1.size; i++) {
			Sumvec->array[i] = Sumvec->array[i] + vec2.array[i];
		}

		return *Sumvec;
	}

	Vector22& operator -(Vector22& vec1, Vector22& vec2) {
		if (vec1.size != vec2.size)
			throw DiscrepancySizeException(vec1.size, vec2.size);
		if (vec1.array == nullptr || vec2.array == nullptr)
			throw NullPtrException();
		Vector22* ResVec = new Vector22(vec1.size, vec1.array);
		for (int i = 0; i < vec1.size; i++) {
			ResVec->array[i] = ResVec->array[i] - vec2.array[i];
		}

		return *ResVec;
	}

	Vector22& operator *(Vector22& vec1, Vector22& vec2) {
		if (vec1.size != vec2.size)
			throw DiscrepancySizeException(vec1.size, vec2.size);
		if (vec1.array == nullptr || vec2.array == nullptr)
			throw NullPtrException();
		Vector22* ResVec = new Vector22(vec1.size, vec1.array);
		for (int i = 0; i < vec1.size; i++) {
			ResVec->array[i] = ResVec->array[i] * vec2.array[i];
		}

		return *ResVec;
	}

	Vector22& operator /(Vector22& vec1, Vector22& vec2) {
		if (vec1.size != vec2.size)
			throw DiscrepancySizeException(vec1.size, vec2.size);
		if (vec1.array == nullptr || vec2.array == nullptr)
			throw NullPtrException();
		Vector22* ResVec = new Vector22(vec1.size, vec1.array);
		for (int i = 0; i < vec1.size; i++) {
			if (vec2.array[i] == 0)
				throw ZeroDivisionException();
			ResVec->array[i] = ResVec->array[i] / vec2.array[i];
		}

		return *ResVec;
	}

	Vector22 operator ++(Vector22& vec1) {
		if (vec1.array == nullptr)
			throw NullPtrException();
		for (int i = 0; i < vec1.size; i++) {
			vec1.array[i] = vec1.array[i] + 1;
		}
		return vec1;
	}

	Vector22 operator --(Vector22& vec1) {
		if (vec1.array == nullptr)
			throw NullPtrException();
		for (int i = 0; i < vec1.size; i++) {
			vec1.array[i] = vec1.array[i] - 1;
		}
		return vec1;
	}

	Vector22 operator ++(Vector22& vec1,int ) {
		if (vec1.array == nullptr)
			throw NullPtrException();
		Vector22* ResVec = new Vector22(vec1.size, vec1.array);
		for (int i = 0; i < vec1.size; i++) {
			vec1.array[i] = vec1.array[i] + 1;
		}
		return *ResVec;
	}

	Vector22 operator --(Vector22& vec1, int) {
		if (vec1.array == nullptr)
			throw NullPtrException();
		Vector22* ResVec = new Vector22(vec1.size, vec1.array);
		for (int i = 0; i < vec1.size; i++) {
			vec1.array[i] = vec1.array[i] - 1;
		}
		return *ResVec;
	}


	bool operator ==(Vector22& vec1, Vector22& vec2) {

		if (vec1.size != vec2.size) return false;
		for (int i = 0; i < vec1.size; i++) {
			if (vec1.array[i] != vec2.array[i]) return false;
		}
		return true;
	}

	bool operator !=(Vector22& vec1, Vector22& vec2) {

		return !(vec1 == vec2);
	}

	Vector22& operator +=(Vector22& vec1, Vector22& vec2) {
		vec1 = vec1 + vec2;
		return vec1;
	}
	
	Vector22& operator -=(Vector22& vec1, Vector22& vec2) {
		vec1 = vec1 - vec2;
		return vec1;
	}

	Vector22& operator *=(Vector22& vec1, Vector22& vec2) {
		vec1 = vec1 * vec2;
		return vec1;
	}

	Vector22& operator /=(Vector22& vec1, Vector22& vec2) {
		vec1 = vec1 / vec2;
		return vec1;
	}


	std::ostream& operator <<(std::ostream& out, Vector22& vec1) {
		out << "size: " << vec1.size << std::endl;
		for (int i = 0; i < vec1.size; i++) {
			out << vec1.array[i] << " ";
		}
		out << std::endl;
		return out;
	}

	std::istream& operator >>(std::istream& in, Vector22& vec1) {
		std::cout << "size: ";
		in >> vec1.size;
		vec1.array = new int[vec1.size];
		for (int i = 0; i < vec1.size; i++) {
			in >> vec1.array[i] ;
		}
		return in;
	}

	void Vector22::setSize(int _size)
	{
		if (_size < 0)
			throw WrongSizeException();
		else
			size = _size;
	}
	int* Vector22::getArray()
	{
		return array;
	}
	void Vector22::setArray(int* _array)
	{
		if (array == nullptr)
			throw NullPtrException();
		else
		{
			array = new int[size];
			for (int i = 0; i < size; i++)
				*(array + i) = *(_array + i);
		}
	}

	void Vector22::push_back(int _num)
	{
		size++;
		int* tmp = new int[size];
		for (int i = 0; i < size - 1; i++)
		{
			tmp[i] = array[i];
		}
		tmp[size - 1] = _num;
		delete[] array;
		array = tmp;
	}
	
void Vector22::erase(int num)
{
	if (num >= size || num < 0)
		throw IndexOutOfRangeException();
	int* lhs = new int[size - 1];
	for (int i = 0; i < num; ++i)
	{
		lhs[i] = array[i];
	}
	for (int i = num + 1; i < size; ++i)
	{
		lhs[i - 1] = array[i];
	}
	delete[] array;
	array = lhs;
	--size;
}

void print_mas(Vector22& new_vector)
{
	if (new_vector.array == nullptr)
		throw NullPtrException();
	for (int i = 0; i < new_vector.size; i++)
	{
		std::cout << new_vector.array[i] << " ";
	}
	std::cout << std::endl;
}
