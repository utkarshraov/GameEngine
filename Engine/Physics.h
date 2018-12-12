#pragma once
#include "SmartPointer.h"
#include "GameObject.h"
#include<vector>
class Rigidbody;

namespace Engine
{
	
		class Physics
		{
		public:
			static Physics *instance;
			void Init();

			void Run();
			static Physics *Instance();
			void addObject(SmartPointer<GameObject> newObject);
			void Update(float frameTime);
			bool removeObject();
			void Shutdown();
		private:
			
			std::vector<SmartPointer<GameObject>> Objects;
		};
	
}