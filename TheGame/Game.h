#pragma once
#include "GameObject.h"
#include "SmartPointer.h"

class Game {



private:
	SmartPointer<GameObject> player;
	SmartPointer<GameObject> obstacle;
	SmartPointer<GameObject> bg;

	Vector2 obsForce;
	char KeyPressID;

	void updatePlayer();
	void updateObstacle();
public:
	static Game * instance;
	static Game *Instance();
	
	SmartPointer<GameObject> getPlayer()
	{
		return player;
	}
	SmartPointer<GameObject> getObstacle()
	{
		return obstacle;
	}
	void Init();
	void Input();
	void Update();
	void Shutdown();

	void setInputKey(char newKey)
	{
		KeyPressID = newKey;
	}
};