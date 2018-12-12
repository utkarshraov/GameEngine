#include "Physics.h"

namespace Engine {


		Physics* Physics::instance = nullptr;


		void Physics::Run()
		{
		}

		Physics * Physics::Instance()
		{
			if (!instance)
			{
				instance = new Physics();
			}
			return instance;
		}
		void Physics::addObject(SmartPointer<GameObject> newObject)
		{
			if (!(newObject->getRigidbody() == nullptr))
			{
				Objects.push_back(newObject);
			}

		}
		void Physics::Update(float frameTime)
		{
			for (auto body : Objects)
			{
				body->getRigidbody()->Update(frameTime);
			}

		}
		void Physics::Shutdown()
		{
			for (auto body : Objects)
			{
				body.~SmartPointer();
			}
			delete instance;
		}
	
}