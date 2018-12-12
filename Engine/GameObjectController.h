#pragma once
#include "GameObject.h"
#include "Vector2.h"

class GameObjectController
{
protected:
	virtual void moveGameObject(GameObject *, Vector2) = 0;
	virtual Vector2 getPosition(GameObject *) = 0;
};

