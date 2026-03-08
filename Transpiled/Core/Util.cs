#line 0 "../../../Source/Core/Util.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Util.nll"
	class Util
	{
		public static void Pad(int nDepth, InternalString sOut)
		{
			for (int i = 0; i < nDepth; i = i + 1)
				sOut.AppendChar('\t');
		}

	}
}

