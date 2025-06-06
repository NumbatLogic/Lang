#pragma once

#include "../../Shared/CPP/Vector.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class InternalString;
	}
}
namespace NumbatLogic
{
	class CLI
	{
		public: static void Run(Vector<const char*>* sArgVector);
	};
}

