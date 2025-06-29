namespace NumbatLogic
{
	class BoolExpr : AST
	{
		public static BoolExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			Token pToken = pTokenContainer.Peek(pOffsetDatum);
			if (pToken == null || (pToken.m_eType != Token.Type.TOKEN_KEYWORD_TRUE && pToken.m_eType != Token.Type.TOKEN_KEYWORD_FALSE))
				return null;
			pOffsetDatum.m_nOffset = pOffsetDatum.m_nOffset + 1;
			BoolExpr pBoolExpr = new BoolExpr();
			pBoolExpr.m_eType = AST.Type.AST_BOOL_EXPR;
			pBoolExpr.m_pFirstToken = pToken;
			NumbatLogic.BoolExpr __616075351 = pBoolExpr;
			pBoolExpr = null;
			return __616075351;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.BOOL);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			m_pFirstToken.Stringify(sOut);
		}

	}
}

