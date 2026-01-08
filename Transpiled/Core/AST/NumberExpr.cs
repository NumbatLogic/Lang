namespace NumbatLogic
{
	class NumberExpr : AST
	{
		public NumberExpr(Token pFirstToken)
		{
			m_eType = AST.Type.AST_NUMBER;
			m_pFirstToken = pFirstToken;
		}

		public static NumberExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			Token pToken = pTokenContainer.PeekExpect(pOffsetDatum, Token.Type.TOKEN_NUMBER);
			if (pToken == null)
				return null;
			pOffsetDatum.m_nOffset = pOffsetDatum.m_nOffset + 1;
			NumberExpr pNumberExpr = new NumberExpr(pToken);
			NumbatLogic.NumberExpr __3368034133 = pNumberExpr;
			pNumberExpr = null;
			return __3368034133;
		}

		public override AST BaseClone()
		{
			NumberExpr pNumberExpr = new NumberExpr(m_pFirstToken);
			NumbatLogic.NumberExpr __3368099729 = pNumberExpr;
			pNumberExpr = null;
			return __3368099729;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.INT);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			m_pFirstToken.Stringify(sOut);
		}

	}
}

