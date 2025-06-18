#include "PointerTest.hpp"
#include "../../../LangShared/Console/CPP/Console.hpp"

namespace NumbatLogic
{
	class Thing;
}
namespace NumbatLogic
{
	Thing::Thing()
	{
		m_ff = 0;
	}

	void PointerTest::Run()
	{
		Console::Log("Pointer test...");
		Thing* pThing = new Thing();
		pThing->m_ff = 0;
		if (pThing) delete pThing;
	}

}

