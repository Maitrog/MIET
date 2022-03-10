#include <iostream>
#include <vector>



int main()
{
	std::vector<std::vector<int>> graph;

	std::vector<bool> used;
	std::vector<int> min_e(graph.size(), INT_MAX), sel_e(graph.size(), -1);
	min_e[0] = 0;

	for (int i = 0; i < graph.size(); i++)
	{
		int v = -1;
		for (int j = 0; j < graph.size(); j++)
		{
			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
				v = j;
			if (min_e[v] == INT_MAX)
			{
				std::cout << "NO MST" << std::endl;
				exit(0);
			}

			used[v] = true;
			if (sel_e[v] != -1)
			{
				std::cout << v << " " << sel_e[v] << std::endl;
			}

			for(int k = 0; k < graph.size(); k++)
				if (graph[v][k] < min_e[k])
				{
					min_e[k] = graph[v][k];
					sel_e[k] = v;
				}
		}
	}


	return 0;
}