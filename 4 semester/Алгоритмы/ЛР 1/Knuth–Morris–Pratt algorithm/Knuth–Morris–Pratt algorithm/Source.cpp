#include <iostream>
#include <vector>



std::vector<int> prefix_function(std::string str)
{
	int n = str.length();
	std::vector<int> pi(n);
	for (int i = 1; i < n; i++)
	{
		int j = pi[i-1];
		while (j > 0 && str[j] != str[i])
			j = pi[j - 1];
		if (str[i] == str[j])
			j++;
		pi[i] = j;
	}
	return pi;
}

bool KnuthMorrisPratt(std::string text, std::string word)
{
	std::string str = word + "#" + text;
	int n = str.length();
	int wl = word.length();
	std::vector<int> pi(n);
	for (int i = wl + 1; i < n; i++)
	{
		int j = pi[i - 1];
		while (j > 0 && str[j] != str[i])
			j = pi[j - 1];
		if (str[i] == str[j])
			j++;
		if (j == wl)
			return true;
		pi[i] = j;
	}
	return false;
}

int main()
{
	if (KnuthMorrisPratt("ajbc", "jsassss"))
		std::cout << "OK";
	else
		std::cout << "GG";
	return 0;
}