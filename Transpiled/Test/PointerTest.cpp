#include "PointerTest.hpp"
#include "../../../LangShared/Console/CPP/Console.hpp"

namespace NumbatLogic
{
	class PointerTest;
	class Console;
	class Thing;
}
#line 0 "/home/cliffya/git/Lang/Source/Test/PointerTest.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Test/PointerTest.nll"
	Thing::Thing()
	{
		m_ff = 0;
	}

#line 10 "/home/cliffya/git/Lang/Source/Test/PointerTest.nll"
	void PointerTest::Run()
	{
		Console::Log("Pointer test...");
#line 14 "/home/cliffya/git/Lang/Source/Test/PointerTest.nll"
		Thing* pThing = new Thing();
		pThing->m_ff = 0;
		if (pThing) delete pThing;
	}

}

