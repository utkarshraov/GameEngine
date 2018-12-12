#pragma once


namespace Engine
{
	namespace Performance
	{

		class PerformanceCollection
		{
		public:

			int                count;
			float            minTime, maxTime, timeSum;

			PerformanceCollection()
			{
				timeSum = 0;
				minTime = 100000000;
				maxTime = 0;
				count = 0;
			}

			void add(float timeStep)
			{
				{
					timeStep = timeStep / 1000;
					timeSum += timeStep;
					count++;

					if (timeStep > maxTime)
						maxTime = timeStep;
					else if (timeStep < minTime)
						minTime = timeStep;
				}

			}

			float averageTimeToRun()
			{
				return timeSum / count;
			}

			float totalTimeSampled()
			{
				return timeSum;
			}

		};
	}//namespace Performance
}//namespace Engine

