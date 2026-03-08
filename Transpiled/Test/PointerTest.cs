#line 0 "../../../Source/Test/PointerTest.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Test/PointerTest.nll"
	class Thing
	{
		public int m_ff;
		public Thing()
		{
		}

	}
#line 8 "../../../Source/Test/PointerTest.nll"
	class PointerTest
	{
		public static void Run()
		{
			Console.Log("Pointer test...");
			Thing pThing = new Thing();
			pThing.m_ff = 0;
		}

	}
}

