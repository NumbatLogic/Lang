namespace NumbatLogic
{
	class Util
	{
		public static void Pad(int nDepth, InternalString sOut)
		{
			for (int i = 0; i < nDepth; i = i + 1)
				sOut.AppendChar('\t');
		}

	}
}

