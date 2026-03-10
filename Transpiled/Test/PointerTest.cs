#line 1 "../../../Source/Test/PointerTest.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Test/PointerTest.nll"
	class Thing
	{
#line 5 "../../../Source/Test/PointerTest.nll"
		public int m_ff;
#line 3 "../../../Source/Test/PointerTest.nll"
		public Thing()
		{
		}

	}
#line 8 "../../../Source/Test/PointerTest.nll"
	class PointerTest
	{
#line 10 "../../../Source/Test/PointerTest.nll"
		public static void Run()
		{
#line 12 "../../../Source/Test/PointerTest.nll"
			Console.Log("Pointer test...");
#line 14 "../../../Source/Test/PointerTest.nll"
			Thing pThing = new Thing();
#line 15 "../../../Source/Test/PointerTest.nll"
			pThing.m_ff = 0;
		}

	}
}

