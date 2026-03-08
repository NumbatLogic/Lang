#line 0 "../../../Source/Core/OutputBuilder.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/OutputBuilder.nll"
	class OutputBuilder
	{
		public InternalString m_sOut;
		public OutputBuilder()
		{
			m_sOut = new InternalString("");
		}

		public void OutputSourceLocation(AST.Language eLanguage, Token pToken)
		{
			if (eLanguage == AST.Language.CPP || eLanguage == AST.Language.C || eLanguage == AST.Language.H || eLanguage == AST.Language.CS)
			{
				m_sOut.Append("#line ");
				m_sOut.AppendInt(pToken.m_nLine);
				m_sOut.Append(" \"");
				m_sOut.Append(pToken.m_sFileName.GetExternalString());
				m_sOut.Append("\"\n");
			}
		}

		~OutputBuilder()
		{
		}

	}
}

