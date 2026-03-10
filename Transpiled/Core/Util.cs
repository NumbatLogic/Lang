#line 1 "../../../Source/Core/Util.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Util.nll"
	class Util
	{
#line 5 "../../../Source/Core/Util.nll"
		public static void Pad(int nDepth, InternalString sOut)
		{
#line 7 "../../../Source/Core/Util.nll"
			for (int i = 0; i < nDepth; i = i + 1)
#line 8 "../../../Source/Core/Util.nll"
				sOut.AppendChar('\t');
		}

	}
}

