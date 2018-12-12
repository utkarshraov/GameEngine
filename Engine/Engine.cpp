
#include "Engine.h"
#include "Physics.h"
#include"Time.h"
#include "CollisionManager.h"
#include "Messaging.h"
#include "LuaScript.h"
#include "Renderer.h"

void KeyCallBack(unsigned int KeyID, bool bWentDown);
GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);

 
namespace Engine
{
	EngineManager * EngineManager::instance = nullptr;
	void EngineManager::EndGame()
	{
		playerDied = true;
		quit = true;
	}
	EngineManager * EngineManager::Instance()
	{
		if (!instance)
		{
			instance = new EngineManager();
		}
		return instance;
	}
	
	void EngineManager::Init()
	{
		playerDied = false;
		Physics::Instance();
		CollisionManager::Instance()->Init();
		Time::Instance()->Init();
		Renderer::Instance()->Init();
	}

	bool EngineManager::Run()
	{
		Time::Instance()->Update();
		Physics::Instance()->Update(Time::Instance()->DeltaTime());
		CollisionManager::Instance()->Run();
		Renderer::Instance()->Run();
		if (playerDied)
		{
			playerDied = playerDied;
		}
		return playerDied;
	}


	void EngineManager::Shutdown()
	{
		Renderer::Instance()->Shutdown();
		Time::Instance()->ShutDown();
		Physics::Instance()->Shutdown();
		CollisionManager::Instance()->Shutdown();
	}

}
