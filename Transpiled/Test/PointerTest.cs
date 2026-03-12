#line 1 "../../../Source/Test/PointerTest.nll"
namespace NumbatLogic
{
	class Thing
	{
		public int m_ff;
#line 3 "../../../Source/Test/PointerTest.nll"
		public Thing()
		{
		}

	}
	class PointerTest
	{
		public static void Run()
		{
			Console.Log("Pointer test...");
#line 14 "../../../Source/Test/PointerTest.nll"
			Thing pThing = new Thing();
			pThing.m_ff = 0;
		}

	}
}

