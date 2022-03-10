#pragma once
#include <iostream>


class Vector
{
private:
	int size;
	int* array;

public:
	Vector();
	Vector(int, int*);
	Vector(const Vector&);
	~Vector();

	int get_size();

	Vector& operator=(const Vector&);

	Vector& operator+();
	Vector& operator-();

	Vector& operator+(Vector&);
	Vector& operator-(Vector&);
	Vector& operator*(Vector&);
	Vector& operator/(Vector&);

	friend Vector operator++(Vector&);
	friend Vector operator--(Vector&);
	friend Vector operator++(Vector&, int);
	friend Vector operator--(Vector&, int);

	friend bool operator==(Vector&, Vector&);
	friend bool operator!=(Vector&, Vector&);

	friend bool operator<(Vector&, Vector&);
	friend bool operator>(Vector&, Vector&);
	friend bool operator<=(Vector&, Vector&);
	friend bool operator>=(Vector&, Vector&);

	Vector& operator+=(Vector&);
	Vector& operator-=(Vector&);
	Vector& operator*=(Vector&);
	Vector& operator/=(Vector&);


	friend std::ostream& operator <<(std::ostream&, Vector&);
	friend std::istream& operator >>(std::istream&, Vector&);

	void set_size(int);
	int* get_array();
	void set_array(int*);
	void push_back(int);
	void erase(int);
};