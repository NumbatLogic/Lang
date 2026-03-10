#include "Util.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class Util;
	class InternalString;
}
#line 0 "../../../Source/Core/Util.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Util.nll"
#line 5 "../../../Source/Core/Util.nll"
	void Util::Pad(int nDepth, InternalString* sOut)
	{
#line 7 "../../../Source/Core/Util.nll"
		for (int i = 0; i < nDepth; i = i + 1)
#line 8 "../../../Source/Core/Util.nll"
			sOut->AppendChar('\t');
	}

}

