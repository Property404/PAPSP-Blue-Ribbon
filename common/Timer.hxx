#pragma once
#include <sys/time.h>

class Timer
{
	struct timeval tv1;
	struct timeval tv2;
	bool started;
	bool stopped;

	public:
	Timer();
	void start();
	void stop();
	double getValue()const;
};
