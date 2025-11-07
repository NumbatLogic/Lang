#include "Util.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class Util;
	class InternalString;
}
namespace NumbatLogic
{
	void Util::Pad(int nDepth, InternalString* sOut)
	{
		for (int i = 0; i < nDepth; i = i + 1)
			sOut->AppendChar('\t');
	}

}

