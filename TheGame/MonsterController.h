#pragma once
#include "GameObjectController.h"

class MonsterController :public GameObjectController
{
	void moveGameObject(GameObject *, Vector2);
	Vector2 getPosition(GameObject *);
	void moveTowardPlayer(GameObject * monster, GameObject * player);
	void randomTeleport(GameObject * monster);
};

void MonsterController::moveGameObject(GameObject * monster, Vector2 pos)
{
	monster->setPosition(pos);
}

Vector2 MonsterController::getPosition(GameObject * monster)
{
	return monster->getPosition();
}

void MonsterController::moveTowardPlayer(GameObject * monster, GameObject * player)
{
	Vector2 temp;
	if (monster->getPosition().getX() > player->getPosition().getX())
		temp.setX(-1);
	if (monster->getPosition().getX() < player->getPosition().getX())
		temp.setX(1);
	if (monster->getPosition().getY() > player->getPosition().getY())
		temp.setY(-1);
	if (monster->getPosition().getY() > player->getPosition().getY())
		temp.setX(1);
	monster->setPosition(monster->getPosition() + temp);
}

void MonsterController::randomTeleport(GameObject * monster)
{
	Vector2 temp(rand() % 100, rand() % 100);
	monster->setPosition(temp);
}