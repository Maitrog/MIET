#include <iostream>
#include <vector>
#include <chrono>


class Timer
{
public:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration< double, std::ratio <1> >;

private:
	std::chrono::time_point<clock_t> beg;
public:

	Timer()
	{
		beg = clock_t::now();
	}

	double elapsed()
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - beg).count();
	}

	void resset()
	{
		beg = clock_t::now();
	}
};

double Sequence(int num)
{
	double an;
	if (num < 0)
		return -1;
	if (num == 0)
		return 1;
	an = 3 * Sequence(num - 1) / num;
	return an;
}

int main()
{
	double p, t;
	Timer timer;
	for (int i = 100; i < 110; i++)
	{
		timer.resset();
		p = Sequence(i);
		t = timer.elapsed();
		std::cout << p << "\t" << t << "\n";
	}
	return 0;
}