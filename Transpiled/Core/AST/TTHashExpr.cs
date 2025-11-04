namespace NumbatLogic
{
	class TTHashExpr : AST
	{
		protected StringExpr m_pStringExpr;
		public TTHashExpr()
		{
			m_eType = AST.Type.AST_TTHASH_EXP;
		}

		public static TTHashExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pTTHashToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_TTHASH);
			if (pTTHashToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			Token pOpenToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT);
			if (pOpenToken == null)
			{
				Console.Log("expected '(' ");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			StringExpr pStringExpr = StringExpr.TryCreate(pTokenContainer, pTempOffset);
			if (pStringExpr == null)
			{
				Console.Log("expected a string to tthash");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			Token pCloseToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT);
			if (pCloseToken == null)
			{
				Console.Log("expected ')' ");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			TTHashExpr pTTHashExpr = new TTHashExpr();
			pTTHashExpr.m_pFirstToken = pTTHashToken;
			pTTHashExpr.m_pStringExpr = pStringExpr;
			NumbatLogic.StringExpr __377119105 = pStringExpr;
			pStringExpr = null;
			pTTHashExpr.AddChild(__377119105);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.TTHashExpr __4265136966 = pTTHashExpr;
			pTTHashExpr = null;
			return __4265136966;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.INT);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (eLanguage == AST.Language.NLL || eLanguage == AST.Language.NLL_DEF)
			{
				sOut.Append("tthash(");
				m_pStringExpr.Stringify(eLanguage, eOutputFile, 0, sOut);
				sOut.AppendChar(')');
			}
			else
			{
				sOut.AppendUint32(ExternalString.GetChecksum(m_pStringExpr.m_pFirstToken.m_sValue.GetExternalString()));
			}
		}

	}
}

