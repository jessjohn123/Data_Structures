#pragma once
#include <ctime>


class DTSTimer
{
	unsigned int startTime;
public:
	DTSTimer()
	{
		reset();
	}

	void reset()
	{
		startTime = clock();
	}

	unsigned int getElapsedTime()
	{
		return (clock() - startTime);
	}

	static void delay(const unsigned int milli)
	{
		unsigned int st = clock();
		while (clock() - st < milli){}
	}

};

