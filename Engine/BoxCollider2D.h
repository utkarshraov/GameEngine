#pragma once
#include "Vector3.h"
#include "Matrix.h"
//#include "GameObject.h"
#include "SmartPointer.h"
class GameObject;
namespace Engine {

		struct AABB
		{
			Vector3 Center;
			Vector3 Extents;
		};

		class BoxCollider2D
		{
		private:
			Matrix model;
			AABB aabb;

			SmartPointer<GameObject>gObject;

		public:
			BoxCollider2D(SmartPointer<GameObject> newGO);
			BoxCollider2D();
			~BoxCollider2D() {};
			Matrix getModelMatrix();
			AABB getAABB();
			void setAABB(Vector3 center, Vector3 extent);
			void Update();
				
			
			void resetMatrix();
			SmartPointer<GameObject> getGameObject();

			bool checkCollision(AABB otherAABB, Vector2 vel, float time, Vector3 & axis);
		};
	}