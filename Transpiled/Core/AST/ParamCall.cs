#line 1 "../../../Source/Core/AST/ParamCall.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ParamCall.nll"
	class ParamCall : AST
	{
#line 5 "../../../Source/Core/AST/ParamCall.nll"
		public static ParamCall TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 7 "../../../Source/Core/AST/ParamCall.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 9 "../../../Source/Core/AST/ParamCall.nll"
			Token m_pFirstToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT);
#line 10 "../../../Source/Core/AST/ParamCall.nll"
			if (m_pFirstToken == null)
			{
#line 12 "../../../Source/Core/AST/ParamCall.nll"
				Console.Log("expected '(' ");
#line 13 "../../../Source/Core/AST/ParamCall.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 14 "../../../Source/Core/AST/ParamCall.nll"
				NumbatLogic.Assert.Plz(false);
#line 15 "../../../Source/Core/AST/ParamCall.nll"
				return null;
			}
#line 17 "../../../Source/Core/AST/ParamCall.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 20 "../../../Source/Core/AST/ParamCall.nll"
			ParamCall pParamCall = new ParamCall();
#line 22 "../../../Source/Core/AST/ParamCall.nll"
			pParamCall.m_eType = AST.Type.AST_PARAM_CALL;
#line 23 "../../../Source/Core/AST/ParamCall.nll"
			pParamCall.m_pFirstToken = m_pFirstToken;
#line 25 "../../../Source/Core/AST/ParamCall.nll"
			while (true)
			{
#line 27 "../../../Source/Core/AST/ParamCall.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) != null)
				{
#line 29 "../../../Source/Core/AST/ParamCall.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 30 "../../../Source/Core/AST/ParamCall.nll"
					break;
				}
#line 33 "../../../Source/Core/AST/ParamCall.nll"
				AST pParam = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 34 "../../../Source/Core/AST/ParamCall.nll"
				if (pParam == null)
				{
#line 36 "../../../Source/Core/AST/ParamCall.nll"
					Console.Log("expected param");
#line 37 "../../../Source/Core/AST/ParamCall.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 38 "../../../Source/Core/AST/ParamCall.nll"
					NumbatLogic.Assert.Plz(false);
				}
				NumbatLogic.AST __3258004090 = pParam;
#line 41 "../../../Source/Core/AST/ParamCall.nll"
				pParam = null;
#line 41 "../../../Source/Core/AST/ParamCall.nll"
				pParamCall.AddChild(__3258004090);
#line 43 "../../../Source/Core/AST/ParamCall.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) != null)
				{
#line 44 "../../../Source/Core/AST/ParamCall.nll"
					continue;
				}
#line 46 "../../../Source/Core/AST/ParamCall.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COMMA) == null)
				{
#line 48 "../../../Source/Core/AST/ParamCall.nll"
					Console.Log("expected comma");
#line 49 "../../../Source/Core/AST/ParamCall.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 50 "../../../Source/Core/AST/ParamCall.nll"
					NumbatLogic.Assert.Plz(false);
				}
#line 52 "../../../Source/Core/AST/ParamCall.nll"
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

#line 59 "../../../Source/Core/AST/ParamCall.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 61 "../../../Source/Core/AST/ParamCall.nll"
			pOutputBuilder.m_sOut.AppendChar('(');
#line 62 "../../../Source/Core/AST/ParamCall.nll"
			AST pParam = m_pFirstChild;
#line 63 "../../../Source/Core/AST/ParamCall.nll"
			while (pParam != null)
			{
#line 65 "../../../Source/Core/AST/ParamCall.nll"
				if (pParam != m_pFirstChild)
#line 66 "../../../Source/Core/AST/ParamCall.nll"
					pOutputBuilder.m_sOut.Append(", ");
#line 67 "../../../Source/Core/AST/ParamCall.nll"
				pParam.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 68 "../../../Source/Core/AST/ParamCall.nll"
				pParam = pParam.m_pNextSibling;
			}
#line 70 "../../../Source/Core/AST/ParamCall.nll"
			pOutputBuilder.m_sOut.AppendChar(')');
		}

	}
}

