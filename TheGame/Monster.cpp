#include "Vector2.h"
#include "Monster.h"
#include<stdlib.h>
#pragma once
Vector2 Up = Vector2(0, 1);
Vector2 Down = Vector2(0, -1);
Vector2 Right = Vector2(1, 0);
Vector2 Left = Vector2(-1, 0);


Monster::Monster(string monName)
{
	Monster::position.setX(rand() % 100);
	Monster::position.setY(rand() % 100);
	name = reinterpret_cast<char *>(operator new(sizeof(monName)));
	name = monName;
}


void Monster::moveMonster()
{
	int random = rand() % 4;
	switch (random)
	{
	case 0:
		moveGameObject(Up);
		break;
	case 1:
		moveGameObject(Left);
		break;
	case 2:
		moveGameObject(Down);
		break;
	case 3:
		moveGameObject(Right);
		break;
	}
	if (position.getX() < 0)
		position.setX(0);
	if (position.getX() > 100)
		position.setX(100);
	if (position.getY() < 0)
		position.setY(0);
	if (position.getY() > 100)
		position.setY(100);
}

bool Monster::areYouFoodYet(Vector2 pos) {
	return false;
}



	
