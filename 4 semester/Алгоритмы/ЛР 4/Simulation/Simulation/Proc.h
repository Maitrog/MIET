#pragma once
#include <iostream>


class Proc
{
private:
	double ProcRate;
	int JobId;
public:
	Proc(int rate);
	int IsProcBusy();
	int RunNewJob(int jobId);
};