#line 1 "../../../Source/Core/ParseDatum.nll"
namespace NumbatLogic
{
	class ParseDatum
	{
		public InternalString m_sInput;
		public InternalString m_sCurrentRead;
#line 8 "../../../Source/Core/ParseDatum.nll"
		public int m_nCurrentReadLine;
		public int m_nCurrentReadColumn;
#line 11 "../../../Source/Core/ParseDatum.nll"
		public InternalString m_sFileName;
		public int m_nLine;
		public int m_nColumn;
#line 15 "../../../Source/Core/ParseDatum.nll"
		public ParseDatum()
		{
			m_sInput = new InternalString("");
			m_sCurrentRead = new InternalString("");
			ClearCurrentRead();
			m_nLine = 1;
		}

		public void ClearCurrentRead()
		{
			m_sCurrentRead.Set("");
			m_nCurrentReadLine = m_nLine;
			m_nCurrentReadColumn = m_nColumn;
		}

#line 3 "../../../Source/Core/ParseDatum.nll"
		~ParseDatum()
		{
		}

	}
}

