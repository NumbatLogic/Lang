#pragma once

#include "../../../LangShared/Vector/CPP/Vector.hpp"

namespace NumbatLogic
{
	template <class T>
	class Vector;
	class InternalString;
}
#line 1 "../../../Source/CLI/CLI.nll"
namespace NumbatLogic
{
	class CLI
	{
		public: static void Run(Vector<const char*>* sArgVector);
	};
}

