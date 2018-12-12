#include "Rigidbody.h"
#include "GameObject.h"
#include "DebugStatement.h"

void Engine::Rigidbody::Update(float deltaTime)
{
	float tempx = (0.5 * ((force.getX() / mass) * (deltaTime * deltaTime)) + (velocity.getX() * deltaTime));
	float tempy = (0.5 * ((force.getY() / mass) * (deltaTime * deltaTime)) + (velocity.getY() * deltaTime));

	velocity = velocity + Vector2(force.getX() / mass * deltaTime, force.getY() / mass * deltaTime);
	//newPosition = object->getPosition() + (velocity * deltaTime) + (((force / mass) / 2) * (deltaTime * deltaTime));
	if (velocity.magnitude() < 0.25)
	{
		velocity = Vector2(0, 0);
	}
	else
	{
		velocity = velocity * drag;
	}
	object->moveGameObject(Vector2(tempx, tempy));
}

void Engine::Rigidbody::applyForce(Vector2 newForce)
{
	force = force + newForce;
}
