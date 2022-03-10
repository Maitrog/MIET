#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>


struct Edge
{
	char vertexes[2];
	int weight;

	Edge(char v1, char v2, int w)
	{
		vertexes[0] = v1;
		vertexes[1] = v2;
		weight = w;
	}

	bool operator<(const Edge& e)
	{
		return weight < e.weight;
	}

	bool operator>(const Edge& e)
	{
		return weight > e.weight;
	}

	bool operator==(const Edge& e)
	{
		return weight == e.weight;
	}

	bool operator<=(const Edge& e)
	{
		return weight <= e.weight;
	}

	bool operator>=(const Edge& e)
	{
		return weight >= e.weight;
	}
};

std::map<char, int> MakeTreeId(std::vector<Edge>& E)
{
	std::map<char, int> tree_id;
	int j = 1;

	for (auto i : E)
	{
		if (!tree_id[i.vertexes[0]])
		{
			tree_id[i.vertexes[0]] = j;
			j++;
		}
		if (!tree_id[i.vertexes[1]])
		{
			tree_id[i.vertexes[1]] = j;
			j++;
		}
	}
	return tree_id;
}

std::vector<Edge> KruskalsAlgorithm(std::vector<Edge>& E)
{
	std::vector<Edge> ostov;
	std::map<char, int> tree_id = MakeTreeId(E);

	for (auto i : E)
	{
		if (tree_id[i.vertexes[0]] != tree_id[i.vertexes[1]])
		{
			ostov.push_back(i);
			int old_id = tree_id[i.vertexes[1]]; int new_id = tree_id[i.vertexes[0]];
			for (auto it = tree_id.begin(); it != tree_id.end(); it++)
			{
				if ((*it).second == old_id)
					(*it).second = new_id;
			}
		}
	}
	return ostov;
}

int GraphWeight(std::vector<Edge>& E)
{
	int res = 0;
	for (auto i : E)
		res += i.weight;

	return res;
}

int main()
{
	std::vector<Edge> E;
	std::vector<Edge> ostov;
	int c;
	int res = 0;

	/*E.push_back(Edge('6', '4', 1));
	E.push_back(Edge('2', '3', 1));
	E.push_back(Edge('2', '4', 2));
	E.push_back(Edge('3', '4', 2));
	E.push_back(Edge('1', '4', 2));
	E.push_back(Edge('3', '5', 3));
	E.push_back(Edge('1', '6', 4));
	E.push_back(Edge('5', '4', 6));
	E.push_back(Edge('1', '2', 7));
	E.push_back(Edge('5', '6', 8));*/

	while (true)
	{
		std::cout << "1.Add edge" << std::endl;
		std::cout << "2.Make ostov" << std::endl;

		std::cin >> c;
		if (c == 1)
		{
			char first, second;
			int weight;
			std::cout << "Enter first vertex (1 char): ";
			std::cin >> first;
			std::cout << "Enter second vertex (1 char): ";
			std::cin >> second;
			std::cout << "Enter edge weight: ";
			std::cin >> weight;

			E.push_back(Edge(first, second, weight));
		}
		else if (c == 2)
		{
			std::sort(E.begin(), E.end());

			ostov = KruskalsAlgorithm(E);
			res = GraphWeight(ostov);

			std::cout << res;
			break;
		}
	}

	
	return 0;
}