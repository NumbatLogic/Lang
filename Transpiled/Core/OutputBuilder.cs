#line 1 "../../../Source/Core/OutputBuilder.nll"
namespace NumbatLogic
{
	class OutputBuilder
	{
		public InternalString m_sOut;
		protected int m_nLastOutOffset;
		protected int m_nLastLine;
		protected InternalString m_sLastFileName;
#line 10 "../../../Source/Core/OutputBuilder.nll"
		public OutputBuilder()
		{
			m_sOut = new InternalString("");
			m_nLastOutOffset = 0;
			m_nLastLine = -1;
			m_sLastFileName = new InternalString("");
		}

		public void UpdateSourceLocation(AST.Language eLanguage, Token pToken)
		{
			if (eLanguage == AST.Language.CPP || eLanguage == AST.Language.C || eLanguage == AST.Language.H || eLanguage == AST.Language.CS)
			{
#line 23 "../../../Source/Core/OutputBuilder.nll"
				int nLength = m_sOut.GetLength();
				for (int i = m_nLastOutOffset; i < nLength; i = i + 1)
				{
					if (m_sOut.GetChar(i) == '\n')
						m_nLastLine = m_nLastLine + 1;
				}
				m_nLastOutOffset = nLength;
#line 31 "../../../Source/Core/OutputBuilder.nll"
				int nDesiredLine = pToken.m_nLine;
				if (eLanguage == AST.Language.CS && pToken.m_nLine == 0)
					nDesiredLine = pToken.m_nLine + 1;
#line 35 "../../../Source/Core/OutputBuilder.nll"
				bool bSameFile = m_sLastFileName.IsEqual(pToken.m_sFileName.GetExternalString());
#line 38 "../../../Source/Core/OutputBuilder.nll"
				if (!bSameFile || m_nLastLine != nDesiredLine)
				{
					m_sOut.Append("#line ");
					m_sOut.AppendInt(nDesiredLine);
					m_sOut.Append(" \"");
					m_sOut.Append(pToken.m_sFileName.GetExternalString());
					m_sOut.Append("\"\n");
#line 46 "../../../Source/Core/OutputBuilder.nll"
					m_sLastFileName.Set(pToken.m_sFileName.GetExternalString());
					m_nLastOutOffset = m_sOut.GetLength();
					m_nLastLine = nDesiredLine;
				}
			}
		}

#line 3 "../../../Source/Core/OutputBuilder.nll"
		~OutputBuilder()
		{
		}

	}
}

