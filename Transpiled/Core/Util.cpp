#include "Util.hpp"
#include "../../../LangShared/Source/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class Util;
	class InternalString;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/Util.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/Util.nll"
#line 5 "/home/cliffya/git/Lang/Source/Core/Util.nll"
	void Util::Pad(int nDepth, InternalString* sOut)
	{
		for (int i = 0; i < nDepth; i = i + 1)
			sOut->AppendChar('\t');
	}

}

