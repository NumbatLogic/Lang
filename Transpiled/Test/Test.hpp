#pragma once

#include "../Core/AST/AST.hpp"

namespace NumbatLogic
{
	class AST;
	class InternalString;
}
namespace NumbatLogic
{
	class Test
	{
		public: static void Run();
		public: static void FullCheck(const char* sInput, AST::Type eAstType);
	};
}

