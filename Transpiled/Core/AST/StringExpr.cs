namespace NumbatLogic
{
	class StringExpr : AST
	{
		public static StringExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			Token pToken = pTokenContainer.PeekExpect(pOffsetDatum, Token.Type.TOKEN_STRING);
			if (pToken == null)
				return null;
			pOffsetDatum.m_nOffset = pOffsetDatum.m_nOffset + 1;
			StringExpr pStringExpr = new StringExpr();
			pStringExpr.m_eType = AST.Type.AST_STRING;
			pStringExpr.m_pFirstToken = pToken;
			NumbatLogic.StringExpr __2586613326 = pStringExpr;
			pStringExpr = null;
			return __2586613326;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.STRING);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			m_pFirstToken.Stringify(sOut);
		}

	}
}

