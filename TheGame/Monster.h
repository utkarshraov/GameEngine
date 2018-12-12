#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include<string>
#include "MemoryManagement.h"
using namespace Engine;
using namespace std;

class Monster :public GameObject {
	
	
public:
	string name;
	Monster(string monName);

	bool areYouFoodYet(Vector2);
	void moveMonster();
};