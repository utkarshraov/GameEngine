
#include"CollisionManager.h"
#include "Rigidbody.h"
#include "Physics.h"
#include "BoxCollider2D.h"
#include "GameObject.h"
#include "Time.h"
#include "Engine.h"

namespace Engine
{

		CollisionManager* CollisionManager::instance = nullptr;

		CollisionManager* CollisionManager::Instance()
		{
			if (!instance)
			{
				instance = new CollisionManager();
			}
			return instance;
		}

		void CollisionManager::Init()
		{

		}
		void CollisionManager::Run()
		{
			for (auto collider : colliders)
			{
				collider->Update();
			}
			if (colliders.size() > 1)
				detectCollision();
		}

		void CollisionManager::Shutdown()
		{
			
			delete instance;
		}

		void CollisionManager::addCollider(SmartPointer<GameObject> newColliderObject)
		{
			if ((newColliderObject->getCollider() == nullptr))
			{
				BoxCollider2D* collider = new BoxCollider2D(newColliderObject);
				
				colliders.push_back(collider);
				newColliderObject->setCollider(collider);
				collider->resetMatrix();
			}
		}

		bool CollisionManager::checkCollision(BoxCollider2D * obj1, BoxCollider2D * obj2, float time, Vector3 axis)
		{
			Matrix coord1to2 = obj2->getModelMatrix().Inversion() * obj1->getModelMatrix();
			Matrix coord2to1 = obj1->getModelMatrix().Inversion() * obj2->getModelMatrix();

			AABB AABB1InCoord2;
			AABB1InCoord2.Center = coord1to2 * obj1->getAABB().Center;
			AABB1InCoord2.Extents = coord1to2 * obj1->getAABB().Extents;

			AABB AABB2InCoord1;
			AABB2InCoord1.Center = coord2to1 * obj2->getAABB().Center;
			AABB2InCoord1.Extents = coord2to1 * obj2->getAABB().Extents;

			Vector2 Velocity1 = obj1->getGameObject()->getRigidbody()->getVelocity();
			Vector2 Velocity2 = obj2->getGameObject()->getRigidbody()->getVelocity();

			Vector2 Vel1InCoord2 = Velocity1 - Velocity2;
			Vector2 Vel2InCoord1 = Velocity2 - Velocity1;

			bool didCollide = obj1->checkCollision(AABB2InCoord1, Vel2InCoord1, time, axis);

			if (didCollide)
			{
				EngineManager::Instance()->playerDied = true;
				axis = coord1to2 * axis;
				axis = axis.normalize();
			}

			return didCollide;


		}

		void CollisionManager::detectCollision()
		{
			float remainTime = Time::Instance()->DeltaTime();
			CollisionPair EarliestPair;
			EarliestPair.colTime = remainTime;

			while (remainTime >= 0.0f)
			{
				float colTime = remainTime;
				Vector3 colNormal;
				bool isCol = false;

				for (int i = 0; i < colliders.size() - 1; ++i)
				{
					for (int j = i + 1; j < colliders.size(); ++j)
					{
						
						if (checkCollision(colliders[i], colliders[j], colTime, colNormal))
						{
							isCol = true;
							if (colTime <= EarliestPair.colTime)
							{
								EarliestPair.col1 = colliders[i];
								EarliestPair.col2 = colliders[j];
								EarliestPair.colTime = colTime;
								EarliestPair.colNormal = colNormal;
							}
						}
					}
				}

				if (isCol)
				{
					EngineManager::Instance()->EndGame();
					handleCollision(EarliestPair);
					remainTime -= EarliestPair.colTime;
					Physics::Instance()->Update(EarliestPair.colTime);
				}
				else
				{
					Physics::Instance()->Update(remainTime);
					break;
				}
			}

		}

		void CollisionManager::handleCollision(CollisionPair & pair)
		{
			Rigidbody* body1 = pair.col1->getGameObject()->getRigidbody();
			Rigidbody* body2 = pair.col2->getGameObject()->getRigidbody();

			if (body1 != NULL && body2 != NULL)
			{
				//Calculate speed
				float mass1 = body1->getMass();
				float mass2 = body2->getMass();
				/*float speed1 = body1->getVelocity().magnitude();
				float speed2 = body2->getVelocity().magnitude();*/
				float speed1 = (body1->getMass() - body2->getMass()) / (body1->getMass() + body2->getMass()) * body1->getVelocity().magnitude() +
					(2.0f * body2->getMass()) / (body1->getMass() + body2->getMass()) * body2->getVelocity().magnitude();

				float speed2 = (body2->getMass() - body1->getMass()) / (body1->getMass() + body2->getMass()) * body2->getVelocity().magnitude() +
					(2.0f * body1->getMass()) / (body1->getMass() + body2->getMass()) * body1->getVelocity().magnitude();

				//Calculate Normalized velocity vector
				Vector3 Vel1 = Vector3(body1->getVelocity().normalise(), 0.0f);
				Vector3 Vel2 = Vector3(body2->getVelocity().normalise(),0.0f);

				if (speed1<0.00001f)
					Vel1 = Vel2;

				if (speed2<0.00001f)
					Vel2 = Vel1;

				if (dot(Vel1, -1.0f * pair.colNormal) > 0)
				{
					Vel1 = (-4.0f * pair.colNormal - Vel1).normalize() * abs(speed1);
					//DEBUG_PRINT("");
				}
				else
				{
					float temp = abs(speed1);
					Vel1 = (-4.0f * pair.colNormal + Vel1).normalize() * abs(speed1);
				}

				if (dot(Vel2, pair.colNormal) > 0)
				{
					Vel2 = (4.0f * pair.colNormal - Vel2).normalize() * abs(speed2);
				}
				else
				{
					Vel2 = (4.0f * pair.colNormal + Vel2).normalize() * abs(speed2);
				}

				body1->setVelocity(Vector2(Vel1.getX(), Vel1.getY()));
				body2->setVelocity(Vector2(Vel2.getX(), Vel2.getY()));

			}

		}
	
}