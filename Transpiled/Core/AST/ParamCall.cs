#line 1 "../../../Source/Core/AST/ParamCall.nll"
namespace NumbatLogic
{
	class ParamCall : AST
	{
		public static ParamCall TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 9 "../../../Source/Core/AST/ParamCall.nll"
			Token m_pFirstToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT);
			if (m_pFirstToken == null)
			{
				Console.Log("expected '(' ");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 20 "../../../Source/Core/AST/ParamCall.nll"
			ParamCall pParamCall = new ParamCall();
#line 22 "../../../Source/Core/AST/ParamCall.nll"
			pParamCall.m_eType = AST.Type.AST_PARAM_CALL;
			pParamCall.m_pFirstToken = m_pFirstToken;
#line 25 "../../../Source/Core/AST/ParamCall.nll"
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
#line 33 "../../../Source/Core/AST/ParamCall.nll"
				AST pParam = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pParam == null)
				{
					Console.Log("expected param");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
				}
				NumbatLogic.AST __3258004090 = pParam;
				pParam = null;
#line 41 "../../../Source/Core/AST/ParamCall.nll"
				pParamCall.AddChild(__3258004090);
#line 43 "../../../Source/Core/AST/ParamCall.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) != null)
				{
#line 44 "../../../Source/Core/AST/ParamCall.nll"
					continue;
				}
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COMMA) == null)
				{
					Console.Log("expected comma");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
#line 55 "../../../Source/Core/AST/ParamCall.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ParamCall __1502847900 = pParamCall;
#line 56 "../../../Source/Core/AST/ParamCall.nll"
			pParamCall = null;
#line 56 "../../../Source/Core/AST/ParamCall.nll"
			return __1502847900;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.m_sOut.AppendChar('(');
			AST pParam = m_pFirstChild;
			while (pParam != null)
			{
				if (pParam != m_pFirstChild)
					pOutputBuilder.m_sOut.Append(", ");
				pParam.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				pParam = pParam.m_pNextSibling;
			}
			pOutputBuilder.m_sOut.AppendChar(')');
		}

	}
}

