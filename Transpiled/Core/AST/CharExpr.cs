namespace NumbatLogic
{
	class CharExpr : AST
	{
		public static CharExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			Token pToken = pTokenContainer.PeekExpect(pOffsetDatum, Token.Type.TOKEN_CHAR);
			if (pToken == null)
				return null;
			pOffsetDatum.m_nOffset = pOffsetDatum.m_nOffset + 1;
			CharExpr pCharExpr = new CharExpr();
			pCharExpr.m_eType = AST.Type.AST_CHAR;
			pCharExpr.m_pFirstToken = pToken;
			{
				NumbatLogic.CharExpr __2809165298 = pCharExpr;
				pCharExpr = null;
				return __2809165298;
			}
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.CHAR);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			m_pFirstToken.Stringify(sOut);
		}

	}
}

