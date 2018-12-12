#pragma once

#include<vector>
#include "GLib.h"
#include "SmartPointer.h"
#include "GameObject.h"


namespace Engine {

	class Renderer {

	private:
		std::vector<SmartPointer<GameObject>> renderObjects;
	public:
		static Renderer * instance;
		static Renderer* Instance();
		void Init();
		void createSprite(char * file, SmartPointer<GameObject> renderObject);
		void Run();
		void Shutdown();
	};
}