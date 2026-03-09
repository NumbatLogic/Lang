#include "Util.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class Util;
	class InternalString;
}
#line 1 "../../../Source/Core/Util.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Util.nll"
#line 6 "../../../Source/Core/Util.nll"
	void Util::Pad(int nDepth, InternalString* sOut)
	{
#line 8 "../../../Source/Core/Util.nll"
		for (int i = 0; i < nDepth; i = i + 1)
#line 9 "../../../Source/Core/Util.nll"
			sOut->AppendChar('\t');
	}

}

