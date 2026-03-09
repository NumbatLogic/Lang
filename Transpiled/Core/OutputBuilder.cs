#line 1 "../../../Source/Core/OutputBuilder.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/OutputBuilder.nll"
	class OutputBuilder
	{
#line 6 "../../../Source/Core/OutputBuilder.nll"
		public InternalString m_sOut;
#line 8 "../../../Source/Core/OutputBuilder.nll"
		public OutputBuilder()
		{
#line 10 "../../../Source/Core/OutputBuilder.nll"
			m_sOut = new InternalString("");
		}

#line 13 "../../../Source/Core/OutputBuilder.nll"
		public void UpdateSourceLocation(AST.Language eLanguage, Token pToken)
		{
#line 15 "../../../Source/Core/OutputBuilder.nll"
			if (eLanguage == AST.Language.CPP || eLanguage == AST.Language.C || eLanguage == AST.Language.H || eLanguage == AST.Language.CS)
			{
#line 17 "../../../Source/Core/OutputBuilder.nll"
				m_sOut.Append("#line ");
#line 18 "../../../Source/Core/OutputBuilder.nll"
				m_sOut.AppendInt(pToken.m_nLine + 1);
#line 19 "../../../Source/Core/OutputBuilder.nll"
				m_sOut.Append(" \"");
#line 20 "../../../Source/Core/OutputBuilder.nll"
				m_sOut.Append(pToken.m_sFileName.GetExternalString());
#line 21 "../../../Source/Core/OutputBuilder.nll"
				m_sOut.Append("\"\n");
			}
		}

#line 4 "../../../Source/Core/OutputBuilder.nll"
		~OutputBuilder()
		{
		}

	}
}

