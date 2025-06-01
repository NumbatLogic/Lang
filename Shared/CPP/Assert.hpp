#pragma once

namespace NumberDuck
{
	namespace Secret
	{
		class nbAssert
		{
			public: static void Assert(bool bTest, const char* sxAssert, const char* sxFile, int nLine);
			public: static void Assert(bool bTest);
		};
	}
}

#ifndef CLIFFY_ASSERT
	#define CLIFFY_ASSERT(x) NumberDuck::Secret::nbAssert::Assert(!!(x), #x, __FILE__, __LINE__)
#endif