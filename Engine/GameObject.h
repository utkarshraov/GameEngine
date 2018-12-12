#pragma once
#include "Vector2.h"
#include"GLib.h"
#include "BoxCollider2D.h"
#include "Rigidbody.h"
using namespace Engine;


class GameObject
{
protected:
	Engine::Vector2 position;
	const char * name;
	float rotation;
	GLib::Sprites::Sprite * sprite;
	BoxCollider2D * collider;
	Engine::Rigidbody * rigidbody;
public:
	GameObject();
	GameObject(Vector2 initPosition, const char * text);
	GameObject( GameObject  & object);
	GameObject(GameObject && object);

	GameObject * self;
	
	inline Engine::Rigidbody * getRigidbody()
	{
		return rigidbody;
	}

	inline void setRigidbody(Engine::Rigidbody * newRB)
	{
		rigidbody = newRB;
	}
	
	inline BoxCollider2D * getCollider()
	{
		return collider;
	}
	
	inline void setCollider(BoxCollider2D * newCollider)
	{
		collider = newCollider;
	}
	inline void setPosition(Vector2 pos)
	{
		position = pos;
	}
	inline Vector2 getPosition() 
	{
		return position;
	}

	inline void setName(const char* text)
	{
		name = text;
	}
	inline const char * getName()  {
		return name;
	}
	inline void moveGameObject(Vector2 direction)
	{
		setPosition(getPosition() + direction);
	}

	inline float getRotation()
	{
		return rotation;
	}

	void setSprite(GLib::Sprites::Sprite * newSprite)
	{
		sprite = newSprite;
	}
	GLib::Sprites::Sprite * getSprite()
	{
		return sprite;
	}
	inline void setRotation(float newRotation)
	{
		rotation = newRotation;
	}
	GameObject & operator=(GameObject & object);
	GameObject & GameObject::operator=(GameObject && object);
	~GameObject()
	{
		/*if (rigidbody)
		{
			delete rigidbody;
		}
		if (collider)
		{
			delete collider;
		}*/
		
	}
	
};

