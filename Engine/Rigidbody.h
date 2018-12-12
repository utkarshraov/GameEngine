#pragma once
#include "Vector2.h"
#include"SmartPointer.h"
#include"BoxCollider2D.h"
class GameObject;


namespace Engine
{
	
		class Rigidbody
		{
		public:
			Rigidbody(SmartPointer<GameObject> physicsObject)
			{
				object = physicsObject;
				collider = nullptr;
				mass = 1;
				drag = 0.1f;
				/*averageFrameTime = 0;*/
				force = Vector2(0,0);
				velocity = Vector2(0, 0);
			}

			Rigidbody(GameObject * physicsObject)
			{
				object = physicsObject;
				collider = nullptr;
				mass = 1;
				drag = 0.1f;
				/*averageFrameTime = 0;*/
				force = Vector2(0, 0);
				velocity = Vector2(0, 0);
			}

			void Update(float deltaTime);
			void applyForce(Vector2 force);

			void setForce(Vector2 newforce) {
				force = newforce;
			}

			float getMass()
			{
				return mass;
			}
			void setMass(float newMass)
			{
				mass = newMass;
			}
			float getDrag()
			{
				return drag;
			}
			void setDrag(float newDrag)
			{
				drag = newDrag;
			}
			Vector2 getVelocity()
			{
				return velocity;
			}
			void setVelocity(Vector2 newVelocity)
			{
				velocity = newVelocity;
			}

		private:
			SmartPointer<GameObject> object;
			BoxCollider2D * collider;
			float mass;
			float drag;
			//float averageFrameTime;
			Vector2 force;
			Vector2 velocity;
		};
	
}