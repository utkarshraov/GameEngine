#pragma once
#include "Vector3.h"
#include "SmartPointer.h"
#include "GameObject.h"

namespace Engine
{
	class EngineManager {
	private:
		bool quit = false;
	public:
		bool playerDied;
		static EngineManager * instance;
		static EngineManager * Instance();
		void Init();
		bool Run();
		void Shutdown();
		void EndGame();
	};
}


