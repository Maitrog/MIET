#include <iostream>
#include <vector>
#include <algorithm>

struct Vertex
{
	int number;
	std::vector<int> nextV;
	std::vector<int> weight;
	int minPath;
	bool used;

	Vertex()
	{
		number = -1;
		minPath = INT_MAX;
		used = false;
	}

	Vertex(int _num, std::vector<int> _nextV, std::vector<int> _weight, int _minPath = INT_MAX, bool _used = false)
	{
		number = _num;
		nextV = _nextV;
		weight = _weight;
		minPath = _minPath;
		used = _used;
	}

	Vertex& operator=(Vertex& v)
	{
		number = v.number;
		nextV = v.nextV;
		weight = v.weight;
		minPath = v.minPath;
		used = v.used;

		return *this;
	}
};

void MinPath(std::vector<Vertex>& g, Vertex& beginV, Vertex endV, int& minPath)
{
	if (beginV.number == endV.number)
	{
		minPath = beginV.minPath;
		return;
	}
	int min = INT_MAX;
	Vertex minV;

	for (int i = 0; i < beginV.nextV.size(); i++)
	{
		g[beginV.nextV[i] - 1].minPath = std::min(g[beginV.nextV[i] - 1].minPath, beginV.minPath + beginV.weight[i]);
	}

	for (int i = 0; i < g.size(); i++)
		if (g[i].minPath <= min && g[i].used == false && g[i].minPath != 0)
		{
			min = g[i].minPath;
			minV = g[i];
		}

	minV.used = true;
	g[minV.number - 1].used = true;

	MinPath(g, minV, endV, minPath);
}

int main()
{
	int p = 0;
	std::vector<Vertex> G;

	/*G.push_back(Vertex(1, std::vector<int> {2, 4, 5, 7}, std::vector<int> {1, 8, 25, 20}, 0, true));
	G.push_back(Vertex(2, std::vector<int> {3, 7}, std::vector<int> {2, 15}));
	G.push_back(Vertex(3, std::vector<int> {6}, std::vector<int> {3}));
	G.push_back(Vertex(4, std::vector<int> {5}, std::vector<int> {9}));
	G.push_back(Vertex(5, std::vector<int> {7}, std::vector<int> {6}));
	G.push_back(Vertex(6, std::vector<int> {2, 7}, std::vector<int> {1, 4}));
	G.push_back(Vertex(7, std::vector<int> {}, std::vector<int> {}));*/

	G.push_back(Vertex(1, std::vector<int> {2, 4, 6}, std::vector<int> {8,5,9}));
	G.push_back(Vertex(2, std::vector<int> {1, 3, 4}, std::vector<int> {8, 2, 1}));
	G.push_back(Vertex(3, std::vector<int> {2, 5, 8}, std::vector<int> {2, 3, 10}));
	G.push_back(Vertex(4, std::vector<int> {1, 2, 5, 6}, std::vector<int> {5, 1, 9, 3}));
	G.push_back(Vertex(5, std::vector<int> {3, 4, 7, 8}, std::vector<int> {3, 9, 0, 6}));
	G.push_back(Vertex(6, std::vector<int> {1, 4, 7}, std::vector<int> {9, 3, 12}));
	G.push_back(Vertex(7, std::vector<int> {5, 6, 8}, std::vector<int> {0, 12, 7}));
	G.push_back(Vertex(8, std::vector<int> {3, 5, 7}, std::vector<int> {10, 6, 7}));


	G[0].minPath = 0;
	G[0].used = true;
	MinPath(G, G[0], G[7], p);

	std::cout << p;

	return 0;
}