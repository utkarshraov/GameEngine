#pragma once
#if defined (_DEBUG) && !defined (DISABLE_DEBUG_PRINT)
#define DEBUG_PRINT(fmt,...) Engine::ConsolePrint((fmt),__VA_ARGS__)
#define EMIT_LOCATION() DEBUG_PRINT("File: %s Line: %d\n",__FILE__,__LINE__)
#else
#define DEBUG_PRINT(fmt,...) void(0)
#endif

namespace Engine {
	void ConsolePrint(const char *, ...);
}