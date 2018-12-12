#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include<string>

using namespace std;



class Players : public GameObject {
protected:
	string playerName;



	

public:
	Players(Vector2 startingPosition, string name)
	{
		position = startingPosition;
		playerName = name;
	}

	void setSprite(GLib::Sprites::Sprite * newSprite)
	{
		sprite = newSprite;
	}
	GLib::Sprites::Sprite * getSprite()
	{
		return sprite;
	}

private:

};