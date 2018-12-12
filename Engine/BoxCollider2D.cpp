#include "BoxCollider2D.h"
#include "GameObject.h"
#include "Time.h"
#include "Engine.h"
namespace Engine {

	
		BoxCollider2D::BoxCollider2D(SmartPointer<GameObject> newGO)
		{
			
			gObject = newGO;
			resetMatrix();
		}


		BoxCollider2D::BoxCollider2D()
		{
			resetMatrix();
		}

		void BoxCollider2D::resetMatrix()
		{
			
			Vector3 translation(gObject->getPosition().getX(), gObject->getPosition().getY(), 0.0f);
			model = model.Translate(translation);
		}

		bool BoxCollider2D::checkCollision(AABB otherAABB, Vector2 vel, float time, Vector3 & axis)
		{
			float dt = Engine::Time::Instance()->DeltaTime();
			float otherLBorder = aabb.Center.getX() - aabb.Extents.getX();
			float otherRBorder = aabb.Center.getX() + aabb.Extents.getX();
			float otherBBorder = aabb.Center.getY() - aabb.Extents.getY();
			float otherTBorder = aabb.Center.getY() + aabb.Extents.getY();

			float LBorder = otherAABB.Center.getX() - otherAABB.Extents.getX();
			float RBorder = otherAABB.Center.getX() + otherAABB.Extents.getX();
			float BBorder = otherAABB.Center.getY() - otherAABB.Extents.getY();
			float TBorder = otherAABB.Center.getY() + otherAABB.Extents.getY();

			float topenX = 0.0f;
			float tcloseX = 0.0f;

			//relatively static and not collide
			if (vel.magnitude() <= 0.0001f && (otherLBorder >= RBorder || otherRBorder <= LBorder) && (otherBBorder >= TBorder || otherTBorder <= BBorder))
				return false;

			if (vel.getX() > 0)
			{
				tcloseX = (otherLBorder - RBorder) / vel.getX();
				topenX = (otherRBorder - LBorder) / vel.getX();
			}
			else if (vel.getX() <= 0)
			{
				tcloseX = (otherRBorder - LBorder) / vel.getX();
				topenX = (otherLBorder - RBorder) / vel.getX();
			}
			else
			{

			}

			if (topenX < 0.0f || tcloseX > dt)
				return false;

			float topenY = 0.0f;
			float tcloseY = 0.0f;

			if (vel.getY() > 0)
			{
				tcloseY = (otherBBorder - TBorder) / vel.getY();
				topenY = (otherTBorder - BBorder) / vel.getY();
			}
			else if (vel.getY() <= 0)
			{
				tcloseY = (otherTBorder - BBorder) / vel.getY();
				topenY = (otherBBorder - TBorder) / vel.getY();
			}
			else
			{

			}

			if (topenY < 0.0f || tcloseY > dt)
				return false;

			if (max(tcloseX, tcloseY) >= min(topenX, topenY))
				return false;

			if (tcloseX > tcloseY)
				if (vel.getX() >= 0)
					axis = Vector3(-1.0f, 0.0f, 0.0f);//collide at left
				else
					axis = Vector3(1.0f, 0.0f, 0.0f);//collide at right
			else
				if (vel.getY() >= 0)
					axis = Vector3(0.0f, -1.0f, 0.0f);//collide at top
				else
					axis = Vector3(0.0f, 1.0f, 0.0f);//collide at bottom

			time = max(tcloseY, tcloseX);
			DEBUG_PRINT("coll");
			EngineManager::Instance()->playerDied = true;
			return true;

		}


		 Matrix BoxCollider2D::getModelMatrix()
		{
			return model;
		}

		 AABB BoxCollider2D::getAABB()
		{
			return aabb;
		}

		 void BoxCollider2D::setAABB(Vector3 center, Vector3 extent)
		{
			aabb.Center = center;
			aabb.Extents = extent;
		}

		 SmartPointer<GameObject> BoxCollider2D::getGameObject()
		{
			return gObject;
		}

		 void BoxCollider2D::Update()
		 {
			 resetMatrix();
			 setAABB(Vector3(gObject->getPosition(), 0.0f), aabb.Extents);
		 }
	
}