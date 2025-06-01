#pragma once

#include "../Core/AST/AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class Test
		{
			public: static void Run();
			public: static void FullCheck(const char* sInput, AST::Type eAstType);
		};
	}
}

