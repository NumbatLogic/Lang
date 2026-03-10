#line 1 "../../../Source/Core/AST/ExpressionStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ExpressionStmt.nll"
	class ExpressionStmt : AST
	{
#line 5 "../../../Source/Core/AST/ExpressionStmt.nll"
		public AST m_pExpression;
#line 7 "../../../Source/Core/AST/ExpressionStmt.nll"
		public ExpressionStmt()
		{
#line 9 "../../../Source/Core/AST/ExpressionStmt.nll"
			m_eType = AST.Type.AST_EXPRESSION_STMT;
#line 10 "../../../Source/Core/AST/ExpressionStmt.nll"
			m_bStatement = true;
		}

#line 13 "../../../Source/Core/AST/ExpressionStmt.nll"
		public static ExpressionStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 15 "../../../Source/Core/AST/ExpressionStmt.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/ExpressionStmt.nll"
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 18 "../../../Source/Core/AST/ExpressionStmt.nll"
			if (pExpression == null)
			{
#line 19 "../../../Source/Core/AST/ExpressionStmt.nll"
				return null;
			}
#line 21 "../../../Source/Core/AST/ExpressionStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
#line 22 "../../../Source/Core/AST/ExpressionStmt.nll"
				return null;
			}
#line 23 "../../../Source/Core/AST/ExpressionStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 26 "../../../Source/Core/AST/ExpressionStmt.nll"
			ExpressionStmt pExpressionStmt = new ExpressionStmt();
#line 27 "../../../Source/Core/AST/ExpressionStmt.nll"
			pExpressionStmt.m_pFirstToken = pExpression.m_pFirstToken;
#line 28 "../../../Source/Core/AST/ExpressionStmt.nll"
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

#line 35 "../../../Source/Core/AST/ExpressionStmt.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 37 "../../../Source/Core/AST/ExpressionStmt.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 39 "../../../Source/Core/AST/ExpressionStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 40 "../../../Source/Core/AST/ExpressionStmt.nll"
			m_pExpression.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 41 "../../../Source/Core/AST/ExpressionStmt.nll"
			pOutputBuilder.m_sOut.Append(";\n");
		}

	}
}

