#include <iostream>
#include <exception>
class Stack
{
private:
	int size;
	int lenth;
	char* data;

public:
	Stack()
	{
		size = 0;
		lenth = 0;
		data = new char[0];
	}

	~Stack()
	{
		delete data;
	}

	int push(const char c)
	{
		lenth++;
		try
		{
			if (size <= lenth)
			{
				size += 10;
				if (size > 1000)
					throw std::exception();
				char* tmp = new char[size];
				for (int i = 0; i < lenth - 1; i++)
				{
					tmp[i] = data[i];
				}
				delete data;
				data = tmp;
			}

			data[lenth - 1] = c;
			return 0;
		}
		catch (std::exception e)
		{
			lenth--;
			size -= 10;
			return 1;
		}
	}

	int pop(char* c)
	{
		if (lenth == 0)
			return 1;
		lenth--;
		*c = data[lenth];
		return 0;	
	}

};

int main()
{
	Stack str;
	str.push('f');
	char c;
	str.pop(&c);
	std::cout << c;
	return 0;
}