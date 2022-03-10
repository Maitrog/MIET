#include <iostream>
#include "Queue.h"


int main()
{
	Queue<int> q(5);
	q.Put(1);
	q.Put(2);
	q.Put(3);
	q.Put(3);
	q.Put(3);
	q.Put(3);

	std::cout << q << std::endl;

	q.Get();
	q.Put(5);
	q.Get();

	std::cout << q;

}