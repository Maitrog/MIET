#include "pch.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <stdio.h>
#include <string>
#include <algorithm>


using namespace std;

void sum(string a, string b)
{
	const int base = 10;
	vector<int> aa, bb;
	vector<int>::iterator itb;
	for (int i = a.length(); i > 0; i-=1)
	{
		if (i < 1)
			aa.push_back(atoi(a.substr(0, i).c_str()));
		else
			aa.push_back(atoi(a.substr(i - 1, 1).c_str()));
	}
	while (aa.size() > 1 && aa.back() == 0)
		aa.pop_back();
	for (int i = b.length(); i > 0; i-=1)
	{
		if (i < 1)
			bb.push_back(atoi(b.substr(0, i).c_str()));
		else
			bb.push_back(atoi(b.substr(i - 1, 1).c_str()));
	}
	while (bb.size() > 1 && bb.back() == 0)
		bb.pop_back();
	
	/*copy(aa.begin(), aa.end(), ostream_iterator<int>(cout, ""));
	cout << endl;
	copy(bb.begin(), bb.end(), ostream_iterator<int>(cout, ""));
	cout << endl;*/

	int carry = 0;
	for (int i = 0; i < max(aa.size(), bb.size()) || carry; i++)
	{
		if (i == aa.size())
			aa.push_back(0);
		aa[i] += carry + (i < bb.size() ? bb[i] : 0);
		carry = aa[i] >= base;
		if (carry)  aa[i] -= base;
	}
	for (auto itb = aa.rbegin(); itb < aa.rend(); itb++)
		cout << *itb;
}

void sub(string m, string n)
{
	const int base = 1000*1000*1000;
	vector<int> M, N;
	vector<int>::iterator itM;
	for (int i = m.length(); i > 0; i -= 9)
	{
		if (i < 9)
			M.push_back(atoi(m.substr(0, i).c_str()));
		else
			M.push_back(atoi(m.substr(i - 9, 9).c_str()));
	}
	while (M.size() > 1 && M.back() == 0)
		M.pop_back();
	for (int i = n.length(); i > 0;i-=9)
	{
		if (i < 9)
			N.push_back(atoi(n.substr(0, i).c_str()));
		else
			N.push_back(atoi(n.substr(i - 9, 9).c_str()));
	}
	while (N.size() > 1 && N.back() == 0)
			N.pop_back();
	int carry = 0;
	for (int i = 0; i < N.size() || carry; i++)
	{
		M[i] -= carry + (i < N.size() ? N[i] : 0);
			carry = M[i] < 0;
			if (carry) M[i] += base;
	}
	while (M.size() > 1 && M.back() == 0)
		M.pop_back();
	for (auto itM = M.rbegin(); itM < M.rend(); itM++)
		cout << *itM;;
}
void mult(string a, string b)
{
	const int base = 1000*1000*1000;
	vector<int> d, e;
	vector<int>::iterator it;
	for (int i = a.length(); i > 0; i -= 9)
		if (i < 9)
			d.push_back(atoi(a.substr(0, i).c_str()));
		else
			d.push_back(atoi(a.substr(i - 9, 9).c_str()));
	while (d.size() > 1 && d.back() == 0)
		d.pop_back();
	for (int i = b.length(); i > 0; i -= 9)
		if (i < 9)
			e.push_back(atoi(b.substr(0, i).c_str()));
		else
			e.push_back(atoi(b.substr(i - 9, 9).c_str()));
	while (e.size() > 1 && e.back() == 0)
		e.pop_back();
	vector<int> c(e.size() + d.size());
	for (size_t i = 0; i < d.size(); i++)
		for (int j = 0, carry = 0; j < (int) e.size() || carry; j++)
		{
			long long cur = c[i + j] + d[i] * 1ll * (j < (int) e.size() ? e[j] : 0) + carry;
			c[i + j] =int (cur % base);
			carry =int (cur / base);
		}
	while (c.size() > 1 && c.back() == 0)
		c.pop_back();
	for (auto it = c.rbegin(); it < c.rend(); it++)
		cout << *it;
	
}

int main()
{
	string a;
	string b;
	getline(cin, a);
	getline(cin, b);
	mult(a, b);
	cout << endl;
	//sub(a, b);
	cout << endl;
	sum(a, b);

	return 0;
}


