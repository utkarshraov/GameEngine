#pragma once


namespace Engine
{
	class Time
	{
	public:
		static Time * instance;

		static Time * Instance();
		
		void Init();
		void Update();
		long timeSinceLastCall();
		long getCurrentCPUFreq();
		long getCurrentCPUTickms();
		void ShutDown();
		float DeltaTime();

	private:
		long getTimeFrequencyms();
		long currentCPUTime;
		long previousCPUTime;
		long defaultCPUFrequency;
		float deltaTime;
	};


}