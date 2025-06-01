#pragma once

#include "../../Shared/CPP/Vector.hpp"

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
		class CLI
		{
			public: static void Run(Vector<const char*>* sArgVector);
		};
	}
}

