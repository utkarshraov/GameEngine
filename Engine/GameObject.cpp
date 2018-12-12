#pragma once
#include "Vector2.h"
#include "GameObject.h"


using namespace Engine;


GameObject::GameObject()
	{
		position.setX(0);
		position.setY(0);
		self = this;
	}
GameObject::GameObject(Vector2 initPosition, const char * text)
	{
		position = initPosition;
		name = text;
		rigidbody = new Engine::Rigidbody(this);
		collider = nullptr;
		self = this;
		
	}
GameObject::GameObject( GameObject & object)
{
	//copy constructor
	position = Vector2(object.getPosition());
}
GameObject::GameObject(GameObject && object)
{
	//Move Constructor
	position = Vector2(object.getPosition());
}

GameObject & GameObject::operator=(GameObject && object)
{
	//move assignment operator
	std::swap(position, object.getPosition());
	return *this;
}
GameObject & GameObject::operator=(GameObject & object)
{
	//assignment operator
	setPosition(object.getPosition());
	return *this;
}

