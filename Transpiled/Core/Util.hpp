#pragma once

namespace NumbatLogic
{
	class InternalString;
}
namespace NumbatLogic
{
	class Util
	{
		public: static void Pad(int nDepth, InternalString* sOut);
		public: static unsigned int BadHash(InternalString* sString);
	};
}

