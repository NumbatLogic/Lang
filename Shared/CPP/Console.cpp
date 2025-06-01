#include "Console.hpp"
#include <stdio.h>

namespace NumberDuck
{
	namespace Secret
	{
		void Console::Log(const char* sxLog)
		{
			printf("%s\n", sxLog);
			fflush(stdout);
		}
	}
}