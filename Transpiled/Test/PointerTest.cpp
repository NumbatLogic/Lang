#include "PointerTest.hpp"
#include "../../../LangShared/Console/CPP/Console.hpp"

namespace NumbatLogic
{
	class PointerTest;
	class Console;
	class Thing;
}
#line 1 "../../../Source/Test/PointerTest.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Test/PointerTest.nll"
#line 4 "../../../Source/Test/PointerTest.nll"
	Thing::Thing()
	{
		m_ff = 0;
	}

#line 9 "../../../Source/Test/PointerTest.nll"
#line 11 "../../../Source/Test/PointerTest.nll"
	void PointerTest::Run()
	{
#line 13 "../../../Source/Test/PointerTest.nll"
		Console::Log("Pointer test...");
		Thing* pThing = new Thing();
#line 16 "../../../Source/Test/PointerTest.nll"
		pThing->m_ff = 0;
		if (pThing) delete pThing;
	}

}

