#pragma once

#include "../../../LangShared/Source/Vector/CPP/Vector.hpp"
#include "../Core/AST/AST.hpp"

namespace NumbatLogic
{
	template <class T>
	class Vector;
	class AST;
	class InternalString;
}
#line 0 "/home/cliffya/git/Lang/Source/Test/Test.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Test/Test.nll"
	class Test
	{
		public: static void Run(Vector<const char*>* sArgVector);
#line 69 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		public: static void FullCheck(const char* sInput, AST::Type eAstType);
	};
}

