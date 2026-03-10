#include "PointerTest.hpp"
#include "../../../LangShared/Console/CPP/Console.hpp"

namespace NumbatLogic
{
	class PointerTest;
	class Console;
	class Thing;
}
#line 0 "../../../Source/Test/PointerTest.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Test/PointerTest.nll"
#line 3 "../../../Source/Test/PointerTest.nll"
	Thing::Thing()
	{
		m_ff = 0;
	}

#line 8 "../../../Source/Test/PointerTest.nll"
#line 10 "../../../Source/Test/PointerTest.nll"
	void PointerTest::Run()
	{
#line 12 "../../../Source/Test/PointerTest.nll"
		Console::Log("Pointer test...");
		Thing* pThing = new Thing();
#line 15 "../../../Source/Test/PointerTest.nll"
		pThing->m_ff = 0;
		if (pThing) delete pThing;
	}

}

