#line 1 "../../../Source/Core/OutputBuilder.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/OutputBuilder.nll"
	class OutputBuilder
	{
#line 5 "../../../Source/Core/OutputBuilder.nll"
		public InternalString m_sOut;
#line 7 "../../../Source/Core/OutputBuilder.nll"
		public OutputBuilder()
		{
#line 9 "../../../Source/Core/OutputBuilder.nll"
			m_sOut = new InternalString("");
		}

#line 12 "../../../Source/Core/OutputBuilder.nll"
		public void UpdateSourceLocation(AST.Language eLanguage, Token pToken)
		{
#line 14 "../../../Source/Core/OutputBuilder.nll"
			if (eLanguage == AST.Language.CPP || eLanguage == AST.Language.C || eLanguage == AST.Language.H || eLanguage == AST.Language.CS)
			{
#line 16 "../../../Source/Core/OutputBuilder.nll"
				m_sOut.Append("#line ");
#line 17 "../../../Source/Core/OutputBuilder.nll"
				if (eLanguage == AST.Language.CS && pToken.m_nLine == 0)
#line 18 "../../../Source/Core/OutputBuilder.nll"
					m_sOut.AppendInt(pToken.m_nLine + 1);
				else
#line 20 "../../../Source/Core/OutputBuilder.nll"
					m_sOut.AppendInt(pToken.m_nLine);
#line 21 "../../../Source/Core/OutputBuilder.nll"
				m_sOut.Append(" \"");
#line 22 "../../../Source/Core/OutputBuilder.nll"
				m_sOut.Append(pToken.m_sFileName.GetExternalString());
#line 23 "../../../Source/Core/OutputBuilder.nll"
				m_sOut.Append("\"\n");
			}
		}

#line 3 "../../../Source/Core/OutputBuilder.nll"
		~OutputBuilder()
		{
		}

	}
}

