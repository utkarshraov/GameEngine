#pragma once

#include "LuaScript.h"


LuaScript::LuaScript(const char * filename)
{





}



//This was given to us in the main function that we started with
void * LoadFile(const char * i_pFilename, size_t & o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE * pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t * pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;

}



SmartPointer<GameObject> LuaScript::CreatePlayerLua()
{


	lua_State* p_LuaState = luaL_newstate();
	assert(p_LuaState);
	luaL_openlibs(p_LuaState);



	size_t fileSize = 0;
	void* p_FileContents = LoadFile("../Engine/Player.lua", fileSize);


	//Important that we do this first, because otherwise the lua stack is populated and we don't
	//get result zero on the pcall (even though it runs because we're doing everything else on top of that
	//unwanted bit. I think
	int result = luaL_loadbuffer(p_LuaState, reinterpret_cast<char *>(p_FileContents), fileSize, nullptr);
	assert(result == 0);

	result = lua_pcall(p_LuaState, 0, 0, 0);
	assert(result == 0);

	if (p_FileContents && fileSize)
	{
		char* somevalue = reinterpret_cast<char*>(p_FileContents);
		DEBUG_PRINT(somevalue);




		result = lua_getglobal(p_LuaState, "Player");
		assert(result == LUA_TTABLE);

		lua_pushstring(p_LuaState, "name");
		result = lua_gettable(p_LuaState, -2);

		assert(result == LUA_TSTRING);

		const char* pName;
		if (result == LUA_TSTRING)
		{
			pName = lua_tostring(p_LuaState, -1);
			assert(pName != nullptr);
			pName = _strdup(pName);

		}
		else
		{
			DEBUG_PRINT("didnt find name");
			pName = _strdup("None");
		}

		if (p_FileContents)
			delete[] p_FileContents;

		lua_close(p_LuaState);


		return SmartPointer<GameObject>(new GameObject(Vector2(0, 0), pName));

		//return SmartPointer<GameObject>(new GameObject(Vector2D(0, 0), pName));


	}

}