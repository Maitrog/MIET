#pragma once
#include <iostream>


class JobStream
{
private:
	double JobIntens;
	int JobId;
public:
	JobStream(int Intens);
	int GetNewJob();
};