#line 1 "../../../Source/Core/ParseDatum.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/ParseDatum.nll"
	class ParseDatum
	{
#line 6 "../../../Source/Core/ParseDatum.nll"
		public InternalString m_sInput;
#line 7 "../../../Source/Core/ParseDatum.nll"
		public InternalString m_sCurrentRead;
#line 9 "../../../Source/Core/ParseDatum.nll"
		public int m_nCurrentReadLine;
#line 10 "../../../Source/Core/ParseDatum.nll"
		public int m_nCurrentReadColumn;
#line 12 "../../../Source/Core/ParseDatum.nll"
		public InternalString m_sFileName;
#line 13 "../../../Source/Core/ParseDatum.nll"
		public int m_nLine;
#line 14 "../../../Source/Core/ParseDatum.nll"
		public int m_nColumn;
#line 16 "../../../Source/Core/ParseDatum.nll"
		public ParseDatum()
		{
#line 18 "../../../Source/Core/ParseDatum.nll"
			m_sInput = new InternalString("");
#line 19 "../../../Source/Core/ParseDatum.nll"
			m_sCurrentRead = new InternalString("");
#line 20 "../../../Source/Core/ParseDatum.nll"
			ClearCurrentRead();
#line 21 "../../../Source/Core/ParseDatum.nll"
			m_nLine = 1;
		}

#line 24 "../../../Source/Core/ParseDatum.nll"
		public void ClearCurrentRead()
		{
#line 26 "../../../Source/Core/ParseDatum.nll"
			m_sCurrentRead.Set("");
#line 27 "../../../Source/Core/ParseDatum.nll"
			m_nCurrentReadLine = m_nLine;
#line 28 "../../../Source/Core/ParseDatum.nll"
			m_nCurrentReadColumn = m_nColumn;
		}

#line 4 "../../../Source/Core/ParseDatum.nll"
		~ParseDatum()
		{
		}

	}
}

