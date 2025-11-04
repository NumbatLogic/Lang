namespace NumbatLogic
{
	class ParamCall : AST
	{
		public ParamDecl m_pFoundParamDecl;
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
				NumbatLogic.AST __1782193718 = pParam;
				pParam = null;
				pParamCall.AddChild(__1782193718);
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
			NumbatLogic.ParamCall __2252655830 = pParamCall;
			pParamCall = null;
			return __2252655830;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			sOut.AppendChar('(');
			AST pParam = m_pFirstChild;
			int index = 0;
			while (pParam != null)
			{
				VarDecl pDeclParam = m_pFoundParamDecl != null ? m_pFoundParamDecl.m_pParamVector.Get(index) : null;
				if (pParam != m_pFirstChild)
					sOut.Append(", ");
				if (eLanguage == AST.Language.CS && pDeclParam != null && pDeclParam.m_pTypeRef.m_bRef)
				{
				}
				pParam.Stringify(eLanguage, eOutputFile, 0, sOut);
				pParam = pParam.m_pNextSibling;
				index++;
			}
			sOut.AppendChar(')');
		}

		public ParamCall()
		{
		}

	}
}

