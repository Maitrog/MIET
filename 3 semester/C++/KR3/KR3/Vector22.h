#pragma once
#include <iostream>
class Vector22
{
private:
	int size;
	int* array;
	friend void print_mas(Vector22&);
public:
	Vector22(int, int*);
	Vector22();
	~Vector22();
	int getSize();
	Vector22& operator =(Vector22&);
	
	friend Vector22& operator +(Vector22&, Vector22&);
	friend Vector22& operator -(Vector22&, Vector22&);
	friend Vector22& operator *(Vector22&, Vector22&);
	friend Vector22& operator /(Vector22&, Vector22&);

	friend Vector22 operator ++(Vector22&);
	friend Vector22 operator --(Vector22&);
	friend Vector22 operator ++(Vector22&, int);
	friend Vector22 operator --(Vector22&, int);
	
	friend bool operator ==(Vector22&, Vector22&);
	friend bool operator !=(Vector22&, Vector22&);

	friend Vector22& operator +=(Vector22&, Vector22&);
	friend Vector22& operator -=(Vector22&, Vector22&);
	friend Vector22& operator *=(Vector22&, Vector22&);
	friend Vector22& operator /=(Vector22&, Vector22&);


	friend std::ostream& operator <<(std::ostream&, Vector22&);
	friend std::istream& operator >>(std::istream&, Vector22&);
	void setSize(int);
	int* getArray();
	void setArray(int*);
	void push_back(int);
	void erase(int);
};