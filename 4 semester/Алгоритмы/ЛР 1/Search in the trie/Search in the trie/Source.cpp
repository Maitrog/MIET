#include <iostream>



const int K = 26;	//Размер алфавита

struct vertex
{
	int next[K];	//Указатели на вершины, в которые ведут ребра
	bool leaf;		//Соответствовует ли какая-либо строка из набора данной вершине
	int p;			//Предок вершины
	char pch;		//Символ, по которому есть переход из предка в данную вершину
	int link;		//Суффиксная ссылка - это вершина, в которой оканчивается наидлиннейший собственный суффикс строки
	int go[K];		//Переходы в автомате по каждому из символов
};

vertex t[255];
int size = 0;


//Добавление слова в бор
void AddString(const std::string& s)
{
	int v = 0;
	for (int i = 0; i < s.length(); i++)
	{
		char c = s[i] - 'a';
		if (t[v].next[c] == -1)
		{
			memset(t[size].next, 255, sizeof t[size].next);
			memset(t[size].go, 255, sizeof t[size].go);
			t[size].link = -1;
			t[size].p = v;
			t[size].pch = c;
			t[v].next[c] = size++;
		}
		v = t[v].next[c];
	}
	t[v].leaf = true;			
}

//Начальная инициализация бора
void init() {
	t[0].p = t[0].link = -1;
	memset(t[0].next, 255, sizeof t[0].next);
	memset(t[0].go, 255, sizeof t[0].go);
	size = 1;
}

int go(int v, char c);

//Функция для вычисления суффиксной ссылки
int get_link(int v) {
	if (t[v].link == -1)
		if (v == 0 || t[v].p == 0)
			t[v].link = 0;
		else
			t[v].link = go(get_link(t[v].p), t[v].pch);
	return t[v].link;
}


//Функция для вычисления перехода
int go(int v, char c) {
	if (t[v].go[c] == -1)
		if (t[v].next[c] != -1)
			t[v].go[c] = t[v].next[c];
		else
			t[v].go[c] = v == 0 ? 0 : go(get_link(v), c);
	return t[v].go[c];
}

//Поиск по бору
bool processText(std::string str)
{
	int v = 0;
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i] - 'a';
		v = go(v, c);
	}
	if (t[v].leaf == true)
		return true;
	else
		return false;

}

int main()
{
	init();
	std::string s = "abs";
	AddString("dfgd");
	AddString("poiwe");
	AddString(s);

	if (processText("abs"))
		std::cout << "OK" << std::endl;
	else
		std::cout << "GG" << std::endl;


	return 0;
}