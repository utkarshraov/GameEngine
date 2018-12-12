#include "Time.h"
#include<Windows.h>

namespace Engine
{
	Time* Time::instance = nullptr;

	Time * Time::Instance()
	{
		if (!instance)
		{
			instance = new Time();
		}
		return instance;
	}
	void Time::ShutDown()
	{
		delete instance;
	}

	void Time::Update()
	{
		deltaTime = (float)timeSinceLastCall() / 1000000;

	}
	float Time::DeltaTime()
	{
		return deltaTime;
	}

	void Time::Init()
	{
		defaultCPUFrequency = getTimeFrequencyms();
		currentCPUTime = getCurrentCPUTickms();
		
	}

	long Time::timeSinceLastCall()
	{
		previousCPUTime = currentCPUTime;
		currentCPUTime = getCurrentCPUTickms();
		return currentCPUTime - previousCPUTime;
	}

	long Time::getCurrentCPUFreq()
	{
		return getTimeFrequencyms();
	}

	long Time::getCurrentCPUTickms()
	{
		LARGE_INTEGER tempCount;
		QueryPerformanceCounter(&tempCount);
		return tempCount.QuadPart;
	}

	long Time::getTimeFrequencyms()
	{
		LARGE_INTEGER tempFreq;
		QueryPerformanceFrequency(&tempFreq);
		return tempFreq.QuadPart;
	}

}