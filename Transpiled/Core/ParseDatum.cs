#line 1 "../../../Source/Core/ParseDatum.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/ParseDatum.nll"
	class ParseDatum
	{
#line 5 "../../../Source/Core/ParseDatum.nll"
		public InternalString m_sInput;
#line 6 "../../../Source/Core/ParseDatum.nll"
		public InternalString m_sCurrentRead;
#line 8 "../../../Source/Core/ParseDatum.nll"
		public int m_nCurrentReadLine;
#line 9 "../../../Source/Core/ParseDatum.nll"
		public int m_nCurrentReadColumn;
#line 11 "../../../Source/Core/ParseDatum.nll"
		public InternalString m_sFileName;
#line 12 "../../../Source/Core/ParseDatum.nll"
		public int m_nLine;
#line 13 "../../../Source/Core/ParseDatum.nll"
		public int m_nColumn;
#line 15 "../../../Source/Core/ParseDatum.nll"
		public ParseDatum()
		{
#line 17 "../../../Source/Core/ParseDatum.nll"
			m_sInput = new InternalString("");
#line 18 "../../../Source/Core/ParseDatum.nll"
			m_sCurrentRead = new InternalString("");
#line 19 "../../../Source/Core/ParseDatum.nll"
			ClearCurrentRead();
#line 20 "../../../Source/Core/ParseDatum.nll"
			m_nLine = 1;
		}

#line 23 "../../../Source/Core/ParseDatum.nll"
		public void ClearCurrentRead()
		{
#line 25 "../../../Source/Core/ParseDatum.nll"
			m_sCurrentRead.Set("");
#line 26 "../../../Source/Core/ParseDatum.nll"
			m_nCurrentReadLine = m_nLine;
#line 27 "../../../Source/Core/ParseDatum.nll"
			m_nCurrentReadColumn = m_nColumn;
		}

#line 3 "../../../Source/Core/ParseDatum.nll"
		~ParseDatum()
		{
		}

	}
}

