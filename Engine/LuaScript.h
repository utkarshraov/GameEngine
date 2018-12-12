#pragma once
#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
#include "assert.h"
#include "DebugStatement.h"
#include "GameObject.h"
#include "SmartPointer.h"

#include <string>
#include <vector>
#include <iostream>



#ifndef LUASCRIPT_H
#define LUASCRIPT_H

/*
TODO: Create a process generic game object function
*/

class LuaScript {

public:


	LuaScript(const char * filename);
	//~LuaScript();


	static SmartPointer<GameObject> CreatePlayerLua();

	//Why does this have to be friend???
	friend void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);


private:
	//lua_State* L;


};
#endif