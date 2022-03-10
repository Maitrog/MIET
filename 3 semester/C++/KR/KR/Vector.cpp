#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Vector.h"
#include "ZeroDivisionException.h"
#include "DiscrepancySizeException.h"
#include "IndexOutOfRangeException.h"
#include "WrongSizeException.h"
#include "NullPtrException.h"




Vector::Vector(int _size, int* _array)
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
Vector::Vector() :Vector(0, nullptr)
{

}

Vector::Vector(const Vector& _vec)
{
	if (_vec.array == nullptr)
		throw NullPtrException();
	if (this != &_vec)
	{
		array = new int[_vec.size];
		size = _vec.size;
		for (int i = 0; i < size; i++)
		{
			array[i] = _vec.array[i];
		}
	}
}
Vector::~Vector()
{
	delete[] array;
}
int Vector::get_size()
{
	return size;
}

Vector& Vector::operator=(const Vector& vec1) {
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

Vector& Vector::operator+()
{
	return *this;
}
Vector& Vector::operator-()
{
	for (int i = 0; i < size; i++)
		array[i] = -array[i];

	return *this;
}

Vector& Vector::operator+(Vector& _vec) {
	if (size != _vec.size)
		throw DiscrepancySizeException(size, _vec.size);
	if (array == nullptr || _vec.array == nullptr)
		throw NullPtrException();

	Vector* result = new Vector(size, array);
	for (int i = 0; i < size; i++) {
		result->array[i] = result->array[i] + _vec.array[i];
	}

	return *result;
}

Vector& Vector::operator-(Vector& _vec) {
	if (size != _vec.size)
		throw DiscrepancySizeException(size, _vec.size);
	if (array == nullptr || _vec.array == nullptr)
		throw NullPtrException();
	Vector* result = new Vector(size, array);
	for (int i = 0; i < size; i++) {
		result->array[i] = result->array[i] - _vec.array[i];
	}

	return *result;
}

Vector& Vector::operator*(Vector& _vec) {
	if (size != _vec.size)
		throw DiscrepancySizeException(size, _vec.size);
	if (array == nullptr || _vec.array == nullptr)
		throw NullPtrException();
	Vector* result = new Vector(size, array);
	for (int i = 0; i < size; i++) {
		result->array[i] = result->array[i] * _vec.array[i];
	}

	return *result;
}

Vector& Vector::operator/(Vector& _vec) {
	if (size != _vec.size)
		throw DiscrepancySizeException(size, _vec.size);
	if (array == nullptr || _vec.array == nullptr)
		throw NullPtrException();
	Vector* result = new Vector(size, array);
	for (int i = 0; i < size; i++) {
		if (_vec.array[i] == 0)
			throw ZeroDivisionException();
		result->array[i] = result->array[i] / _vec.array[i];
	}

	return *result;
}

Vector operator++(Vector& vec1) {
	if (vec1.array == nullptr)
		throw NullPtrException();
	for (int i = 0; i < vec1.size; i++) {
		vec1.array[i] = vec1.array[i] + 1;
	}
	return vec1;
}

Vector operator--(Vector& vec1) {
	if (vec1.array == nullptr)
		throw NullPtrException();
	for (int i = 0; i < vec1.size; i++) {
		vec1.array[i] = vec1.array[i] - 1;
	}
	return vec1;
}

Vector operator ++(Vector& vec1, int) {
	if (vec1.array == nullptr)
		throw NullPtrException();
	Vector* ResVec = new Vector(vec1.size, vec1.array);
	for (int i = 0; i < vec1.size; i++) {
		vec1.array[i] = vec1.array[i] + 1;
	}
	return *ResVec;
}

Vector operator--(Vector& vec1, int) {
	if (vec1.array == nullptr)
		throw NullPtrException();
	Vector* ResVec = new Vector(vec1.size, vec1.array);
	for (int i = 0; i < vec1.size; i++) {
		vec1.array[i] = vec1.array[i] - 1;
	}
	return *ResVec;
}


bool operator==(Vector& vec1, Vector& vec2) 
{

	if (vec1.size != vec2.size) 
		return false;

	for (int i = 0; i < vec1.size; i++) {
		if (vec1.array[i] != vec2.array[i]) 
			return false;
	}
	return true;
}

bool operator!=(Vector& vec1, Vector& vec2) 
{

	return !(vec1 == vec2);
}

bool operator>(Vector& vec1, Vector& vec2)
{
	for (int i = 0; i < std::min(vec1.size, vec2.size); i++)
	{
		if (vec1.array[i] > vec2.array[i])
			return true;
		else
			return false;
	}
}

bool operator<(Vector& vec1, Vector& vec2)
{
	for (int i = 0; i < std::min(vec1.size, vec2.size); i++)
	{
		if (vec1.array[i] < vec2.array[i])
			return true;
		else
			return false;
	}
}

bool operator>=(Vector& vec1, Vector& vec2)
{
	return !(vec1 < vec2);
}

bool operator<=(Vector& vec1, Vector& vec2)
{
	return !(vec1 > vec2);
}

Vector& Vector::operator+=(Vector& _vec) {
	*this = *this + _vec;
	return *this;
}

Vector& Vector::operator-=(Vector& _vec) {
	*this = *this - _vec;
	return *this;
}

Vector& Vector::operator*=(Vector& _vec) {
	*this = *this * _vec;
	return *this;
}

Vector& Vector::operator/=(Vector& _vec) {
	*this = *this / _vec;
	return *this;
}


std::ostream& operator<<(std::ostream& out, Vector& vec1) {
	out << "size: " << vec1.size << std::endl;
	for (int i = 0; i < vec1.size; i++) {
		out << vec1.array[i] << " ";
	}
	out << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, Vector& vec1) {
	std::cout << "size: ";
	in >> vec1.size;
	if (vec1.size < 0)
		throw WrongSizeException();
	vec1.array = new int[vec1.size];
	for (int i = 0; i < vec1.size; i++) {
		in >> vec1.array[i];
	}
	return in;
}

void Vector::set_size(int _size)
{
	if (_size < 0)
		throw WrongSizeException();
	else
		size = _size;
}
int* Vector::get_array()
{
	return array;
}
void Vector::set_array(int* _array)
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

void Vector::push_back(int _num)
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

void Vector::erase(int num)
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

