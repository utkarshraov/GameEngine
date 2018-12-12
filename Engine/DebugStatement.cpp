#include <assert.h>		// for assert()
#include <stdarg.h>		// for va_<xxx>
#include <stdio.h>		// for vsprintf_s()
#include <Windows.h>	// for OutputDebugStringA(). Uggh.. this pulls in a lot of Windows specific stuff


namespace Engine
{

	void ConsolePrint(const char * statement, ...)
	{
		assert(statement);

		const size_t tempLength = 256;
		char tempString[tempLength] = "DEBUG: ";

		strcat_s(tempString, statement);
		strcat_s(tempString, "\n");

		const size_t outputLength = tempLength + 32;

		char outputString[outputLength];

		// define a variable argument list variable 
		va_list arguments;

		// initialize it. second parameter is variable immediately
		// preceeding variable arguments
		va_start(arguments, statement);

		// (safely) print our formatted string to a char buffer
		vsprintf_s(outputString, outputLength, tempString, arguments);

		va_end(arguments);

		OutputDebugStringA(outputString);
	}

}