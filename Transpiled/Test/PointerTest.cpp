#include "PointerTest.hpp"
#include "../../../LangShared/Console/CPP/Console.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class Thing;
	}
}
namespace NumberDuck
{
	namespace Secret
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
}

