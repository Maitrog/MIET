#pragma once
#include <iostream>


template<class Type>
class Queue
{
private:
	Type* pMem;
	int MemSize;
	int MaxMemSize = 25;
	int DataCount;
	int Hi;
	int Li;

protected:
	int GetNextIndex(int index)
	{
		if (index < MemSize - 1)
			return (index + 1);
		else
			return 0;
	}

	int GetNextIndex(int index) const
	{
		if (index < MemSize - 1)
			return (index + 1);
		else
			return 0;
	}

public:
	Queue<Type>()
	{
		MemSize = MaxMemSize;
		pMem = new Type[MemSize];
		DataCount = 0;
		Li = 0;
		Hi = - 1;
	}

	Queue<Type>(int size)
	{
		MemSize = size;
		pMem = new Type[MemSize];
		DataCount = 0;
		Li = 0;
		Hi = - 1;
	}

	~Queue()
	{
		delete[] pMem;
	}

	void Put(Type elem)
	{
		if (!IsFull()) 
		{
			Hi = GetNextIndex(Hi);
			pMem[Hi] = elem;
			DataCount++;
		}
	}

	Type Get()
	{
		if (!IsEmpty())
		{
			Type tmp = pMem[Li];
			Li = GetNextIndex(Li);
			DataCount--;
			return tmp;
		}
	}

	bool IsFull()
	{
		return DataCount == MemSize;
	}

	bool IsEmpty()
	{
		return DataCount == 0;
	}

	int size()
	{
		return MemSize;
	}

	int count()
	{
		return DataCount;
	}

	friend std::ostream& operator<<(std::ostream& out, const Queue& q)
	{
		int k = 0;
		for (int i = q.Li; k < q.DataCount; i = q.GetNextIndex(i), k++)
		{
			out << q.pMem[i] << " ";
		}
		return out;
	}
};