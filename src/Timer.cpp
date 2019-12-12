#include "Timer.hxx"
#include <stdexcept>

Timer::Timer()
{
	started = false;
	stopped = false;

	tv1.tv_sec = 0;
	tv1.tv_usec = 0;
	tv2.tv_sec = 0;
	tv2.tv_usec = 0;
}

void Timer::start()
{
	if(started)
		throw std::runtime_error("Already started");

	started = true;

	// Do this last to get the most accurate result
	restart();
}

void Timer::restart()
{
	if(!started)
		throw std::runtime_error("Not started");

	// Do this last to get the most accurate result
	gettimeofday(&tv1, (struct timezone*)0);
}

void Timer::stop()
{
	// Do this first to get the most accurate result
	gettimeofday(&tv2, (struct timezone*)0);

	if(!started)
		throw std::runtime_error("Not started");
	if(stopped)
		throw std::runtime_error("Already stopped");

	stopped = true;
}

double Timer::getValue() const
{
	if(!stopped)
		throw std::runtime_error("Not stopped!");
	return (double) (tv2.tv_usec- tv1.tv_usec)/1000000.0+(tv2.tv_sec-tv1.tv_sec);
}

double Timer::getCurrent() const
{
	struct timeval tv3;
	gettimeofday(&tv3, (struct timezone*)0);

	if(stopped)
		throw::std::runtime_error("Stopped");

	return (double) (tv3.tv_usec- tv1.tv_usec)/1000000.0+(tv3.tv_sec-tv1.tv_sec);
}
