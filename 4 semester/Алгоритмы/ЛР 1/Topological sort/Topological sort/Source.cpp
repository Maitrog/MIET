#include <iostream>
#include <vector>

struct vertex
{
	std::string element;
	std::vector<int> next;
	int count_prev = 0;
	int count_next = 0;
};

std::vector<vertex> t;

void AddPair(std::string s1, std::string s2)
{
	bool flag_s1 = false;
	bool flag_s2 = false;
	int index_s1 = 0;
	int index_s2 = 0;
	for (int i = 0; i < t.size(); i++)
	{
		if (!flag_s1 && t[i].element == s1)
		{
			t[i].count_next++;
			index_s1 = i;
			flag_s1 = true;
		}

		if (!flag_s2 && t[i].element == s2)
		{
			t[i].count_prev++;
			index_s2 = i;
			flag_s2 = true;
		}
	}
	if (!flag_s1)
	{
		t.push_back(vertex{ s1, std::vector<int>{}, 0, 1 });
		index_s1 = t.size() - 1;
	}
	if (!flag_s2)
	{
		t.push_back(vertex{ s2, std::vector<int>{}, 1, 0 });
		index_s2 = t.size() - 1;
	}
	t[index_s1].next.push_back(index_s2);
}

std::vector<int> get_Q()
{
	std::vector<int> Q;
	for (int i = 0; i < t.size(); i++)
		if (t[i].count_prev == 0)
			Q.push_back(i);
	return Q;
}

void upd_Q(std::vector<int>* Q, int index)
{
	for (int i = 0; i < t[(*Q)[index]].next.size(); i++)
	{
		t[t[(*Q)[index]].next[i]].count_prev--;
		if (t[t[(*Q)[index]].next[i]].count_prev == 0)
			(*Q).push_back(t[(*Q)[index]].next[i]);
	}
}

void TopologicalSort()
{
	std::vector<int> Q;
	int R = 0;
	int L = 0;
	int max = t.size();
	Q = get_Q();
	

	
	while (L < max)
	{
		if (Q.size() == 0)
		{
			std::cout << "Solution not exist" << std::endl;
			return;
		}
		R = Q[Q.size() - 1];
		std::cout << t[Q[0]].element << std::endl;
		upd_Q(&Q, 0);
		Q.erase(Q.begin());
		L++;
	}
	

}

int main()
{
	AddPair("b", "a");
	AddPair("b", "d");
	AddPair("d", "c");
	AddPair("a", "c");
	AddPair("c", "e");
	AddPair("c", "f");

	TopologicalSort();

	return 0;
}