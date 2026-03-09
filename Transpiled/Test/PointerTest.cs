#line 1 "../../../Source/Test/PointerTest.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Test/PointerTest.nll"
	class Thing
	{
#line 6 "../../../Source/Test/PointerTest.nll"
		public int m_ff;
#line 4 "../../../Source/Test/PointerTest.nll"
		public Thing()
		{
		}

	}
#line 9 "../../../Source/Test/PointerTest.nll"
	class PointerTest
	{
#line 11 "../../../Source/Test/PointerTest.nll"
		public static void Run()
		{
#line 13 "../../../Source/Test/PointerTest.nll"
			Console.Log("Pointer test...");
			Thing pThing = new Thing();
#line 16 "../../../Source/Test/PointerTest.nll"
			pThing.m_ff = 0;
		}

	}
}

