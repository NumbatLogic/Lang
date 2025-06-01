#pragma once

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
		class Util
		{
			public: static void Pad(int nDepth, InternalString* sOut);
			public: static unsigned int BadHash(InternalString* sString);
		};
	}
}

