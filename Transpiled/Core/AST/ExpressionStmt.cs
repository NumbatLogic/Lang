namespace NumbatLogic
{
	class ExpressionStmt : AST
	{
		public AST m_pExpression;
		public ExpressionStmt()
		{
			m_eType = AST.Type.AST_EXPRESSION_STMT;
			m_bStatement = true;
		}

		public static ExpressionStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
				return null;
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			ExpressionStmt pExpressionStmt = new ExpressionStmt();
			pExpressionStmt.m_pFirstToken = pExpression.m_pFirstToken;
			pExpressionStmt.m_pExpression = pExpression;
			NumbatLogic.AST __2491310498 = pExpression;
			pExpression = null;
			pExpressionStmt.AddChild(__2491310498);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ExpressionStmt __2577616101 = pExpressionStmt;
			pExpressionStmt = null;
			return __2577616101;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			Util.Pad(nDepth, sOut);
			m_pExpression.Stringify(eLanguage, eOutputFile, nDepth, sOut);
			sOut.Append(";\n");
		}

	}
}

