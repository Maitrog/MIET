//#include <iostream>
//#include <vector>
//#include <numeric>
//#include <utility>
//#include <algorithm>
//
//void InitGraph(std::vector<std::vector<int>>& g, int countV)
//{
//	
//	for (int i = 0; i < countV; i++)
//	{
//		g.push_back(std::vector<int>(0));
//		for (int j = 0; j < countV; j++)
//		{
//			if (i == j)
//				g[i].push_back(INT_MAX);
//			else
//				g[i].push_back(rand());
//		}
//	}
//}
//
//struct Graph
//{
//	std::vector<std::vector<int>> g;
//	int Bound;
//	bool IsUsed = false;
//	int first = -1;
//	int second = -1;
//	bool IsLeft = false;
//
//	Graph()
//	{
//		Bound = INT_MAX;
//	}
//
//	Graph(int size)
//	{
//		InitGraph(g, size);
//		Bound = INT_MAX;
//	}
//
//	Graph(std::vector<std::vector<int>>& gr)
//	{
//		g = gr;
//	}
//
//	void PrintGraph()
//	{
//		std::cout << std::endl;
//		for (int i = 0; i < g.size(); i++)
//		{
//			for (int j = 0; j < g[i].size(); j++)
//				if (g[i][j] > INT_MAX / 2)
//					std::cout << "-\t";
//				else
//					std::cout << g[i][j] << "\t";
//			std::cout << std::endl;
//		}
//		std::cout << std::endl;
//	}
//};
//
//std::vector<long long> ReductionByColumn(std::vector<std::vector<int>>& g)
//{
//	std::vector<long long> hi(g.size(), INT_MAX);
//
//	for (int j = 0; j < g.size(); j++)
//		for (int i = 0; i < g.size(); i++)
//			if (g[i][j] < hi[j])
//				hi[j] = g[i][j];
//
//	for (int j = 0; j < g.size(); j++)
//		for (int i = 0; i < g.size(); i++)
//			if (hi[j] < INT_MAX/2)
//				g[i][j] -= hi[j];
//			else
//				hi[j] = 0;
//	
//	return hi;
//}
//
//std::vector<long long> ReductionByRow(std::vector<std::vector<int>>& g)
//{
//	std::vector<long long> hj(g.size(), INT_MAX);
//
//	for (int i = 0; i < g.size(); i++)
//		for (int j = 0; j < g.size(); j++)
//			if (g[i][j] < hj[i])
//				hj[i] = g[i][j];
//
//	for (int i = 0; i < g.size(); i++)
//		for (int j = 0; j < g.size(); j++)
//			if (hj[i] < INT_MAX/2)
//				g[i][j] -= hj[i];
//			else
//				hj[i] = 0;
//
//	return hj;
//}
//
//int GetFine(std::vector<std::vector<int>>& g, int i, int j)
//{
//	int minCol = INT_MAX, minRow = INT_MAX;
//	for (int k = 0; k < g.size(); k++)
//		if (g[k][j] < minCol && k!=i)
//			minCol = g[k][j];
//
//	for (int k = 0; k < g.size(); k++)
//		if (g[i][k] < minRow && k!=j)
//			minRow = g[i][k];
//
//	return minRow + minCol;
//}
//
//std::vector<int> MaxFine(std::vector<std::vector<int>>& g)
//{
//	int indexCol = -1, indexRow = -1, D = 0;
//	for (int i = 0; i < g.size(); i++)
//		for (int j = 0; j < g.size(); j++)
//		{
//			if (g[i][j] == 0)
//			{
//				int newD = GetFine(g, i, j);
//				if (newD >= D && newD < INT_MAX/2)
//				{
//					D = newD;	
//					indexCol = i;
//					indexRow = j;
//				}
//			}
//		}
//	return std::vector<int>{indexCol, indexRow, D};
//}
//
//void ZeroFind(std::vector<std::vector<int>>& g, std::vector<int>& path)
//{
//	std::vector<std::pair<int, int>> p;
//	std::pair<int, int> last;
//	for (int i = 0; i < g.size(); i++)
//		for (int j = 0; j < g[i].size(); j++)
//			if (g[i][j] == 0)
//				p.push_back(std::pair<int, int>(i, j));
//
//	for (int i = 0; i < p.size(); i++)
//		for (int j = 0; j < p.size(); j++)
//			if (p[j].first == path[path.size() - 1] && p[j].second != path[0])
//			{
//				if (std::find(path.begin(), path.end(), p[j].first) == path.end())
//					path.push_back(p[j].first);
//				if (std::find(path.begin(), path.end(), p[j].second) == path.end())
//					path.push_back(p[j].second);
//			}
//			else if (p[j].second == path[0])
//				last = p[j];
//
//	path.push_back(last.second);
//}
//
//void Voyager(std::vector<Graph>& graphs, int& index, std::vector<int>& path)
//{
//	Graph G;
//	std::vector<int> v;
//	std::vector<long long> Hi, Hj;
//	int minBound = INT_MAX, usedIndex = 0;
//	long long R, R2;
//
//	for (int i = 0; i < path.size(); i++)
//	{
//		graphs[index].g[graphs[index].second][path[i]] = INT_MAX;
//	}
//
//	G.g = graphs[index].g;
//
//	Hj = ReductionByRow(graphs[index].g);
//	Hi = ReductionByColumn(graphs[index].g);
//
//	R = std::accumulate(Hi.begin(), Hi.end(), 0) + std::accumulate(Hj.begin(), Hj.end(), 0);
//
//	v = MaxFine(graphs[index].g);
//
//	if (v[0] == -1 && v[1] == -1)
//	{
//		ZeroFind(G.g, path);
//		return;
//	}
//
//	G.first = v[0];
//	G.second = v[1];
//
//	G.IsLeft = true;
//	G.Bound = R + v[2];
//	if (graphs.size() > 2 && R == 0)
//		G.Bound = G.Bound + graphs[index].Bound;
//
//	G.PrintGraph();
//
//	graphs.push_back(G);
//	if(std::find(path.begin(), path.end(), v[0]) == path.end())
//		path.push_back(v[0]);
//	if (std::find(path.begin(), path.end(), v[1]) == path.end())
//		path.push_back(v[1]);
//
//	for (int i = 0; i < graphs[index].g.size(); i++)
//		graphs[index].g[i][v[1]] = INT_MAX;
//	for (int j = 0; j < graphs[index].g.size(); j++)
//		graphs[index].g[v[0]][j] = INT_MAX;
//
//	graphs[index].g[v[1]][path[0]] = INT_MAX;
//
//	Hj = ReductionByRow(graphs[index].g);
//	Hi = ReductionByColumn(graphs[index].g);
//
//	R2 = std::accumulate(Hi.begin(), Hi.end(), 0) + std::accumulate(Hj.begin(), Hj.end(), 0);
//
//	v = MaxFine(graphs[index].g);
//
//	G.g = graphs[index].g;
//	G.Bound = R2 + R;
//	if (graphs.size() > 2 && R == 0)
//		G.Bound = G.Bound + graphs[index].Bound;
//
//	G.PrintGraph();
//
//	graphs.push_back(G);
//
//
//	for(int i = 0; i < graphs.size(); i++)
//		if(graphs[i].Bound <= minBound && graphs[i].IsUsed == false)
//		{
//			minBound = graphs[i].Bound;
//			usedIndex = i;
//		}
//	graphs[usedIndex].IsUsed = true;
//
//	Voyager(graphs, usedIndex, path);
//}
//
//void PrintPath(std::vector<int> path)
//{
//	std::cout << path[0];
//	for (int i = 1; i < path.size(); i++)
//	{
//		std::cout << " -> " << path[i];
//	}
//}
//
//int main()
//{
//	time_t k;
//	srand(time(&k));
//	Graph G;
//	std::vector<std::vector<int>> g;
//	std::vector<int> Hi, Hj, path, v;
//	std::vector<Graph> graphs;
//	int R, index = 0;
//	InitGraph(g, 6);
//
//	/*g = { {INT_MAX, 68, 73, 24, 70, 9},
//		{58, INT_MAX, 16, 44, 11, 92},
//		{63, 9, INT_MAX, 86, 13, 18},
//		{17, 34, 76, INT_MAX, 52, 70},
//		{60, 18, 3, 45, INT_MAX, 58},
//		{16, 82, 11, 60, 48, INT_MAX} };*/
//
//	g = { {INT_MAX, 7, 12, 25, 10 },
//		{10, INT_MAX, 9, 5, 11 },
//		{13, 8, INT_MAX, 6, 4 },
//		{6, 11, 15, INT_MAX, 15 },
//		{5, 9, 12, 17, INT_MAX } };
//
//	G.g = g;
//
//	graphs.push_back(G);
//	Voyager(graphs, index, path);
//
//	PrintPath(path);
//	std::cout << std::endl << graphs[graphs.size() - 1].Bound;
//	
//	}

#include <stdio.h>
#include <iostream>
int uz[50][50];
int vich[50][50];
int mstr[50];
int msto[50];
int kp[50];
int msh[50][50];
int mshstr[50][50];
int mshsto[50][50];
int d[50][2], c[50];
int g[50][2];
int k[50][2];
int m[50][2];
int a, b, e, f;
int h;
int n;
int sp = 0;
int r;
int i, j;

int main()
{

    //Vvod razmera matrici
    std::cin >> r;

    //prisv diag elm znach -444
    for (i = 0; i <= (r - 1); i++)
    {
        uz[i][i] = -444;
    }

    //vvod elem matrizi
    for (i = 0; i <= (r - 1); i++)
    {
        for (j = 0; j <= (r - 1); j++)
        {
            if (uz[i][j] != -444)scanf_s("%d", &uz[i][j]);
        }
    }

    //viv ish dan
    for (i = 0; i <= (r - 1); i++)
    {
        printf("\n");
        for (j = 0; j <= (r - 1); j++)
        {
            printf("\t%d", uz[i][j]);
        }
    }

    //prisv perv znach matr g[][]
    for (j = 0; j <= (r - 1); j++)
    {
        g[j][0] = j + 1;
        g[j][1] = j + 1;
    }

    //pech perv znach g
    for (i = 0; i <= (r - 1); i++)
    {
        printf("\n");
        for (j = 0; j <= 1; j++)
        {
            printf("\t%d", g[i][j]);
        }
    }

    //prisv znach matr vich
    for (i = 0; i <= (r - 1); i++)
    {
        for (j = 0; j <= (r - 1); j++)
        {
            vich[i][j] = uz[i][j];
        }
    }

    //prisv perv znach 0 matr m[][]
    for (j = 0; j <= (r - 2); j++)
    {
        m[j][0] = 0;
        m[j][1] = 0;
    }

    //nachalo zikla shsaga zadachi
    for (h = 1; h <= 5; h++)
    {
        printf("\n%dиру", h);

        //vichisl min elem strok
        for (i = 0; i <= (r - h); i++)
        {
            for (j = 0; j <= (r - h); j++)
            {
                if (vich[i][j] != -444) { mstr[i] = vich[i][j]; break; }
            }
        }
        for (i = 0; i <= (r - h); i++)
        {
            for (j = 0; j <= (r - h); j++)
            {
                if (vich[i][j] != -444)
                {
                    if (mstr[i] > vich[i][j])mstr[i] = vich[i][j];
                }
            }
        }

        //pech min elem strok
        for (i = 0; i <= (r - h); i++)
        {
            printf("\n%d", mstr[i]);
        }

        //vichit min elem strok
        for (i = 0; i <= (r - h); i++)
        {
            for (j = 0; j <= (r - h); j++)
            {
                if (vich[i][j] != -444)vich[i][j] = vich[i][j] - mstr[i];
            }
        }

        //viv posle vich min elem strok
        for (i = 0; i <= (r - h); i++)
        {
            printf("\n");
            for (j = 0; j <= (r - h); j++)
            {
                printf("\t%d", vich[i][j]);
            }
        }

        //vichisl min elem stolbc
        for (j = 0; j <= (r - h); j++)
        {
            for (i = 0; i <= (r - h); i++)
            {
                if (vich[i][j] != -444) { msto[j] = vich[i][j]; break; }
            }
        }

        for (j = 0; j <= (r - h); j++)
        {
            for (i = 0; i <= (r - h); i++)
            {
                if (vich[i][j] != -444)
                {
                    if (msto[j] > vich[i][j])msto[j] = vich[i][j];
                }
            }
        }

        //pech min el sto
        for (j = 0; j <= (r - h); j++)
        {
            printf("\n%d", msto[j]);
        }

        //vichit min elem stolb
        for (j = 0; j <= (r - h); j++)
        {
            for (i = 0; i <= (r - h); i++)
            {
                if (vich[i][j] != -444)vich[i][j] = vich[i][j] - msto[j];
            }
        }

        //vivod posle vich min el stol
        for (i = 0; i <= (r - h); i++)
        {
            printf("\n");
            for (j = 0; j <= (r - h); j++)
            {
                printf("\t%d", vich[i][j]);
            }
        }

        //zapom sum konst priv na shage 
        for (i = 0; i <= (r - h); i++)
        {
            kp[h - 1] = kp[h - 1] + mstr[i] + msto[i];
        }

        //pech sum konst priv
        printf("\n%d", kp[h - 1]);

        //perech na shage poslednem
        if (h == r - 1)goto e;

        //prisv msh -111
        for (i = 0; i <= (r - h); i++)
        {
            for (j = 0; j <= (r - h); j++)
            {
                msh[i][j] = -111;
            }
        }

        //vich min shtr u nuley v stolb i strokah
        for (i = 0; i <= (r - h); i++)
        {
            for (j = 0; j <= (r - h); j++)
            {
                if (vich[i][j] == 0)
                {
                    //vich shtr v str
                    for (a = 0; a <= (r - h); a++)
                    {
                        if (vich[i][a] != -444)
                        {
                            if (a != j)
                            {
                                mshstr[i][j] = vich[i][a]; goto A;
                            }
                        }
                    }

                A:
                    for (a = 0; a <= (r - h); a++)
                    {
                        if (vich[i][a] != -444)
                        {
                            if (a != j)
                            {
                                if (mshstr[i][j] > vich[i][a])mshstr[i][j] = vich[i][a];
                            }
                        }
                    }

                    //vich shtr v stolb u nuley
                    for (b = 0; b <= (r - h); b++)
                    {
                        if (vich[b][j] != -444)
                        {
                            if (b != i)
                            {
                                mshsto[i][j] = vich[b][j]; goto B;
                            }
                        }
                    }
                B:
                    for (b = 0; b <= (r - h); b++)
                    {
                        if (vich[b][j] != -444)
                        {
                            if (b != i)
                            {
                                if (mshsto[i][j] > vich[b][j])mshsto[i][j] = vich[b][j];
                            }
                        }
                    }


                    //vich shtrafa
                    msh[i][j] = mshstr[i][j] + mshsto[i][j];

                }
            }
        }

        //vivod strafov na shage
        for (i = 0; i <= (r - h); i++)
        {
            printf("\n");
            for (j = 0; j <= (r - h); j++)
            {
                printf("\t%d", msh[i][j]);
            }
        }

        //nahoz perv strafa maks
        for (i = 0; i <= (r - h); i++)
        {
            for (j = 0; j <= (r - h); j++)
            {
                if (msh[i][j] != -111)
                {
                    c[h - 1] = msh[i][j]; d[h - 1][0] = i; d[h - 1][1] = j; goto C;
                }
            }
        }
    C:
        for (i = 0; i <= (r - h); i++)
        {
            for (j = 0; j <= (r - h); j++)
            {
                if (msh[i][j] != 111)
                {
                    if (msh[i][j] > c[h - 1])
                    {
                        c[h - 1] = msh[i][j]; d[h - 1][0] = i; d[h - 1][1] = j;
                    }
                }
            }
        }

        //pech max shtraf na shage, n stroki i stolbza virez na shage
        std::cout << "\n" << c[h - 1] << "\t" << d[h - 1][0] << "\t" << d[h - 1][1];

        //prisv matr k znach na shage
        k[h - 1][0] = g[d[h - 1][0]][0];
        k[h - 1][1] = g[d[h - 1][1]][1];

        //uresanie stroki matrizi
        for (i = 0; i <= (r - h - 1); i++)
        {
            if (i == d[h - 1][0])
            {
                for (e = i; e <= (r - h - 1); e++)
                {
                    for (f = 0; f <= (r - h); f++)
                    {
                        vich[e][f] = vich[e + 1][f];
                    }
                }
            }
        }

        //pech posle urez stroki
        for (i = 0; i <= (r - h - 1); i++)
        {
            printf("\n");
            for (j = 0; j <= (r - h); j++)
            {
                printf("\t%d", vich[i][j]);
            }
        }

        //uresanie stolbza matrizi
        for (j = 0; j <= (r - h - 1); j++)
        {
            if (j == d[h - 1][1])
            {
                for (e = j; e <= (r - h - 1); e++)
                {
                    for (f = 0; f <= (r - h - 1); f++)
                    {
                        vich[f][e] = vich[f][e + 1];
                    }
                }
            }
        }

        //pech posle urez stolbza
        for (i = 0; i <= (r - h - 1); i++)
        {
            printf("\n");
            for (j = 0; j <= (r - h - 1); j++)
            {
                printf("\t%d", vich[i][j]);
            }
        }

        //prisv matr g nomerov strok i stolbzov
        for (i = d[h - 1][0]; i <= (r - h - 1); i++)
            g[i][0] = g[i + 1][0];
        for (i = d[h - 1][1]; i <= (r - h - 1); i++)
            g[i][1] = g[i + 1][1];

        //pech tek znach g
        for (i = 0; i <= (r - h - 1); i++)
        {
            printf("\n");
            for (j = 0; j <= 1; j++)
            {
                printf("\t%d", g[i][j]);
            }
        }

        //proverka est li protiv elem, esli est prisv beskonechn
        for (i = 0; i <= (r - h - 1); i++)
        {
            for (j = 0; j <= (r - h - 1); j++)
            {
                if (k[h - 1][0] == g[j][1] && k[h - 1][1] == g[i][0])
                {
                    vich[i][j] = -444; printf("\n%d", vich[d[h - 1][1]][d[h - 1][0]]); goto D;
                }
            }
        }

        //nahoz vseh zepey(prisoed dugi v nachale)
        for (i = 0; i < (h - 1); i++)
        {
            if (k[h - 1][0] == k[i][1])
            {
                m[h - 1][0] = k[i][0]; m[h - 1][1] = k[h - 1][1];
            }
        }

        //nahoz vseh zepey(prisoed dugi v konce)
        for (i = 0; i < (h - 1); i++)
        {
            if (k[h - 1][1] == k[i][0])
            {
                if (m[h - 1][0] == 0)
                {
                    m[h - 1][0] = k[h - 1][0]; m[h - 1][1] = k[i][1];
                }
                else m[h - 1][1] = k[i][1];
            }
        }

        //proverka mozno prisoedinit zepi i prisoedinenie
        for (i = 0; i < h - 1; i++)
        {
            if (m[i][0] != 0)
            {
                if (k[h - 1][0] == m[i][1])
                {
                    m[h - 1][0] = m[i][0];
                }
            }
        }
        for (i = 0; i < h - 1; i++)
        {
            if (m[i][0] != 0)
            {
                if (k[h - 1][1] == m[i][0])
                {
                    m[h - 1][1] = m[i][1];
                }
            }
        }

        //zapret zepi na shage - prisv -444

        for (i = 0; i <= (r - h - 1); i++)
        {
            for (j = 0; j <= (r - h - 1); j++)
            {
                if (m[h - 1][0] == g[j][1] && m[h - 1][1] == g[i][0])
                {
                    vich[i][j] = -444;
                }
            }
        }

    D:

        //pech dugi m na shage
        printf("\n%d", m[h - 1][0]);
        printf("\n%d", m[h - 1][1]);

    }

e:
    //vivod matrizi d
    for (i = 0; i <= (r - 3); i++)
    {
        printf("\n");
        for (j = 0; j <= 1; j++)
        {
            printf("\t%d", d[i][j]);
        }
    }

    //prisv dvuch posl strok v mass k
    int l = 2;
    for (i = 0; i <= 1; i++)
    {
        for (j = 0; j <= 1; j++)
        {
            if (vich[i][j] == 0)
            {
                k[r - l][0] = g[i][0]; k[r - l][1] = g[j][1]; l = l - 1;
            }

        }
    }

    //rasch stoim proezda
    for (i = 0; i <= r - 1; i++)
    {
        sp = sp + uz[k[i][0] - 1][k[i][1] - 1];
    }

    //vivod stoim proezda
    printf("\n%d", sp);

    //vivod matrizi k
    for (i = 0; i <= (r - 1); i++)
    {
        printf("\n");
        for (j = 0; j <= 1; j++)
        {
            printf("\t%d", k[i][j]);
        }
    }


}