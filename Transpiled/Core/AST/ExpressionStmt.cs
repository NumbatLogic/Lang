#line 1 "../../../Source/Core/AST/ExpressionStmt.nll"
namespace NumbatLogic
{
	class ExpressionStmt : AST
	{
		public AST m_pExpression;
#line 7 "../../../Source/Core/AST/ExpressionStmt.nll"
		public ExpressionStmt()
		{
			m_eType = AST.Type.AST_EXPRESSION_STMT;
			m_bStatement = true;
		}

		public static ExpressionStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/ExpressionStmt.nll"
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
#line 19 "../../../Source/Core/AST/ExpressionStmt.nll"
				return null;
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
#line 22 "../../../Source/Core/AST/ExpressionStmt.nll"
				return null;
			}
#line 23 "../../../Source/Core/AST/ExpressionStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 26 "../../../Source/Core/AST/ExpressionStmt.nll"
			ExpressionStmt pExpressionStmt = new ExpressionStmt();
			pExpressionStmt.m_pFirstToken = pExpression.m_pFirstToken;
			pExpressionStmt.m_pExpression = pExpression;
			NumbatLogic.AST __1929334319 = pExpression;
#line 29 "../../../Source/Core/AST/ExpressionStmt.nll"
			pExpression = null;
#line 29 "../../../Source/Core/AST/ExpressionStmt.nll"
			pExpressionStmt.AddChild(__1929334319);
#line 31 "../../../Source/Core/AST/ExpressionStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ExpressionStmt __490873359 = pExpressionStmt;
#line 32 "../../../Source/Core/AST/ExpressionStmt.nll"
			pExpressionStmt = null;
#line 32 "../../../Source/Core/AST/ExpressionStmt.nll"
			return __490873359;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 39 "../../../Source/Core/AST/ExpressionStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
			m_pExpression.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			pOutputBuilder.m_sOut.Append(";\n");
		}

	}
}

