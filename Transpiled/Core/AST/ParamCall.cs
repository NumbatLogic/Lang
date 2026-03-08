#line 1 "../../../Source/Core/AST/ParamCall.nll"
namespace NumbatLogic
{
	class ParamCall : AST
	{
		public static ParamCall TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token m_pFirstToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT);
			if (m_pFirstToken == null)
			{
				Console.Log("expected '(' ");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			ParamCall pParamCall = new ParamCall();
			pParamCall.m_eType = AST.Type.AST_PARAM_CALL;
			pParamCall.m_pFirstToken = m_pFirstToken;
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
				AST pParam = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pParam == null)
				{
					Console.Log("expected param");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
				}
				NumbatLogic.AST __3258004090 = pParam;
				pParam = null;
				pParamCall.AddChild(__3258004090);
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) != null)
				{
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
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ParamCall __1502847900 = pParamCall;
			pParamCall = null;
			return __1502847900;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder out)
		{
			out.m_sOut.AppendChar('(');
			AST pParam = m_pFirstChild;
			while (pParam != null)
			{
				if (pParam != m_pFirstChild)
					out.m_sOut.Append(", ");
				pParam.Stringify(eLanguage, eOutputFile, 0, out);
				pParam = pParam.m_pNextSibling;
			}
			out.m_sOut.AppendChar(')');
		}

	}
}

