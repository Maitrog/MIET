#include <iostream>
#include <vector>
#include <algorithm>



struct Vertex
{
	long long int number;
	std::vector<long long int> prevV;
	std::vector<long long int> nextV;
	std::vector<long long int> weightPrev;
	long long int minPath;
	bool used;

	Vertex()
	{
		number = -1;
		minPath = INT_MAX;
		used = false;
	}

	Vertex(long long int _num, std::vector<long long int> _prevV, std::vector<long long int> _nextV, std::vector<long long int> _weight, long long int _minPath = INT_MAX, bool _used = false)
	{
		number = _num;
		prevV = _prevV;
		nextV = _nextV;
		weightPrev = _weight;
		minPath = _minPath;
		used = _used;
	}

	Vertex& operator=(Vertex& v)
	{
		number = v.number;
		prevV = v.prevV;
		nextV = v.nextV;
		weightPrev = v.weightPrev;
		minPath = v.minPath;
		used = v.used;

		return *this;
	}
};

void MinPath(std::vector<Vertex>& g)
{
	std::vector<long long int> q;
	q.push_back(1);
	/*for (long long int i = 0; i < g[0].nextV.size(); i++)
	{
		q.push_back(g[0].nextV[i]);
		g[g[0].nextV[i] - 1].used = true;
	}*/

	long long int min = INT_MAX;
	Vertex minV;

	for (long long int i = 0; i < g.size(); i++)
	{
		long long int localMin = INT_MAX;
		for (long long int j = 0; j < g[q[0] - 1].prevV.size(); j++)
			g[q[0] - 1].minPath = std::min(g[q[0] - 1].minPath, g[g[q[0] - 1].prevV[j] - 1].minPath + g[q[0] - 1].weightPrev[j]);

		for (long long int j = 0; j < g[q[0] - 1].nextV.size(); j++)
		{
			bool flag = true;
			for (long long int k = 0; k < g[g[q[0] - 1].nextV[j] - 1].prevV.size(); k++)
				if (g[g[g[q[0] - 1].nextV[j] - 1].prevV[k] - 1].used == false)
					flag = false;


			if (flag && g[g[q[0] - 1].nextV[j] - 1].used == false)
			{
				q.push_back(g[q[0] - 1].nextV[j]);
				g[g[q[0] - 1].nextV[j] - 1].used = true;
			}
		}
		q.erase(q.begin());
	}

}

int main()
{
	long long int p = 0;
	std::vector<Vertex> G;

	G.push_back(Vertex(1, std::vector<long long int> {},			std::vector<long long int> {2, 4, 5, 7},	std::vector<long long int> {}, 0, true));
	G.push_back(Vertex(2, std::vector<long long int> {1},			std::vector<long long int> {3, 7},			std::vector<long long int> {1}));
	G.push_back(Vertex(3, std::vector<long long int> {2},			std::vector<long long int> {6},				std::vector<long long int> {2}));
	G.push_back(Vertex(4, std::vector<long long int> {1},			std::vector<long long int> {5},				std::vector<long long int> {8}));
	G.push_back(Vertex(5, std::vector<long long int> {1, 4},		std::vector<long long int> {7},				std::vector<long long int> {25, 9}));
	G.push_back(Vertex(6, std::vector<long long int> {3},			std::vector<long long int> {7},				std::vector<long long int> {3}));
	G.push_back(Vertex(7, std::vector<long long int> {1, 2, 5, 6},	std::vector<long long int> {},				std::vector<long long int> {20, 15, 6, 4}));

	/*G.push_back(Vertex(1, std::vector<long long int> {},		std::vector<long long int> {2,4,5}, std::vector<long long int> {}, 0, true));
	G.push_back(Vertex(2, std::vector<long long int> {1},		std::vector<long long int> {3,6},	std::vector<long long int> {6}));
	G.push_back(Vertex(3, std::vector<long long int> {2},		std::vector<long long int> {4,7},	std::vector<long long int> {5}));
	G.push_back(Vertex(4, std::vector<long long int> {1,3},		std::vector<long long int> {7},		std::vector<long long int> {7,2}));
	G.push_back(Vertex(5, std::vector<long long int> {1},		std::vector<long long int> {6,7},	std::vector<long long int> {9}));
	G.push_back(Vertex(6, std::vector<long long int> {2,5},		std::vector<long long int> {7},		std::vector<long long int> {0,4}));
	G.push_back(Vertex(7, std::vector<long long int> {3,4,5,6},	std::vector<long long int> {},		std::vector<long long int> {3,1,8,4}));*/

	MinPath(G);

	std::cout << G[6].minPath;

	return 0;
}