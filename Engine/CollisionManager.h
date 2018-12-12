#pragma once
#include <vector>
#include"BoxCollider2D.h"

namespace Engine
{

	class CollisionPair
	{
	public:
		BoxCollider2D* col1;
		BoxCollider2D* col2;
		float colTime;
		Vector3 colNormal;

		CollisionPair() :
			col1(NULL), col2(NULL) {}

	};
	
	class CollisionManager
		{
		private:

		public:
			static CollisionManager *instance;
			CollisionManager() {}
			~CollisionManager() {}

			void Init();
			void Run();
			void Shutdown();

			std::vector<BoxCollider2D*> colliders;

			static CollisionManager* Instance();

			void addCollider(SmartPointer<GameObject> newGO);

			bool checkCollision(BoxCollider2D * obj1, BoxCollider2D * obj2, float time, Vector3 axis);
			void detectCollision();
			void handleCollision(CollisionPair & pair);
		};
	
}