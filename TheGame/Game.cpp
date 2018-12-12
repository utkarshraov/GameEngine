#include "Game.h"
#include "GLib.h"
#include "CollisionManager.h"
#include "Physics.h"
#include "Engine.h"
#include "Renderer.h"

void KeyCallBack(unsigned int KeyID, bool bWentDown);

Game * Game::instance = nullptr;



Game * Game::Instance()
{
	if (!instance)
	{
		instance = new Game();
	}
	return instance;
}

void Game::Init()
{
	player = new GameObject(Vector2(-500, -200), "Utkarsh");
	obstacle = new GameObject(Vector2(300, 200), "Obstacle");
	bg = new GameObject(Vector2(0, -400), "BG");

	Renderer::Instance()->createSprite("data\\spaceship.dds", player);
	Renderer::Instance()->createSprite("data\\rock.dds",obstacle);
	Renderer::Instance()->createSprite("data\\bg.dds", bg);
	Physics::Instance()->addObject(player);
	Physics::Instance()->addObject(obstacle);
	obsForce = Vector2(-30000, 0);

	CollisionManager::Instance()->addCollider(player);
	CollisionManager::Instance()->addCollider(obstacle);
	player->getCollider()->setAABB(Vector3(-500, -200, 0), Vector3(130, 90, 0));
	obstacle->getCollider()->setAABB(Vector3(300, 200, 0), Vector3(50, 50, 0));
	GLib::SetKeyStateChangeCallback(KeyCallBack);
}


void Game::Input()
{
	switch (KeyPressID)
	{
	case 'w':
		player->getRigidbody()->applyForce(Vector2(0, 100));

		break;
	case 's':
		player->getRigidbody()->applyForce(Vector2(0, -100));
		break;
	case 'a':
		player->getRigidbody()->applyForce(Vector2(0, 0));
		break;
	default:
		KeyPressID = 'p';
		player->getRigidbody()->setForce(Vector2(0, 0));
		break;
	}
}
void Game::Update()
{
	GLib::SetKeyStateChangeCallback(KeyCallBack);
	Input();
	updatePlayer();
	updateObstacle();

}

void Game::Shutdown()
{
	player.~SmartPointer();
	obstacle.~SmartPointer();
	bg.~SmartPointer();
}

void Game::updatePlayer()
{
	player->getCollider()->setAABB(Vector3(player->getPosition().getX(), player->getPosition().getY() + 90, 0), Vector3(130, 90, 0));
	
	
	if (player->getPosition().getY() >= 400) {
		player->setPosition(Vector2(player->getPosition().getX(), -400));


	}
	else if (player->getPosition().getY() <= -400)
	{
		player->setPosition(Vector2(player->getPosition().getX(), 300));
	}

}

void Game::updateObstacle()
{
	obstacle->getCollider()->setAABB(Vector3(obstacle->getPosition().getX(), obstacle->getPosition().getY() + 120, 0), Vector3(160, 120, 0));
	obstacle->getRigidbody()->setForce(obsForce);
	if (obstacle->getPosition().getX() <= -800) {
		int yVal = rand() % 200;
		if (yVal % 2 == 0)
			yVal *= -1;
		obstacle->setPosition(Vector2(800, yVal));
		obsForce = obsForce + Vector2(-3000, 0);

	}

}



void KeyCallBack(unsigned int KeyID, bool bWentDown)
{
	switch (KeyID)
	{
	case 0x0057:
		if (bWentDown)
			Game::Instance()->setInputKey('w');
		else
			Game::Instance()->setInputKey('a');
		break;
	case 0x0053:
		if (bWentDown)
			Game::Instance()->setInputKey('s');
		else
			Game::Instance()->setInputKey('a');
		break;
	default:
		Game::Instance()->setInputKey('p');
		break;
	}
}
