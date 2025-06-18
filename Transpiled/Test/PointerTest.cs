namespace NumbatLogic
{
	class Thing
	{
		public int m_ff;
		public Thing()
		{
		}

	}
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

