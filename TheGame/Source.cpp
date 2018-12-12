#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>



#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG
#include "Engine.h"
#include "Game.h"





int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "TheGame", -1, 1920, 1080);
	bool endGame = false;
	Engine::EngineManager::Instance()->Init();
	Game::Instance()->Init();
	do {
		endGame = Engine::EngineManager::Instance()->Run();
		Game::Instance()->Update();
	} while (!endGame);
	Game::Instance()->Shutdown();
	Engine::EngineManager::Instance()->Shutdown();

	}





