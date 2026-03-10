#line 1 "../../../Source/Core/AST/ReturnStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ReturnStmt.nll"
	class ReturnStmt : AST
	{
#line 5 "../../../Source/Core/AST/ReturnStmt.nll"
		public AST m_pExpression;
#line 7 "../../../Source/Core/AST/ReturnStmt.nll"
		public ReturnStmt()
		{
#line 9 "../../../Source/Core/AST/ReturnStmt.nll"
			m_eType = AST.Type.AST_RETURN_STMT;
#line 10 "../../../Source/Core/AST/ReturnStmt.nll"
			m_bStatement = true;
		}

#line 13 "../../../Source/Core/AST/ReturnStmt.nll"
		public static ReturnStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 15 "../../../Source/Core/AST/ReturnStmt.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/ReturnStmt.nll"
			Token pReturnToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_RETURN);
#line 18 "../../../Source/Core/AST/ReturnStmt.nll"
			if (pReturnToken == null)
			{
#line 19 "../../../Source/Core/AST/ReturnStmt.nll"
				return null;
			}
#line 20 "../../../Source/Core/AST/ReturnStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 22 "../../../Source/Core/AST/ReturnStmt.nll"
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 24 "../../../Source/Core/AST/ReturnStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
#line 25 "../../../Source/Core/AST/ReturnStmt.nll"
				return null;
			}
#line 26 "../../../Source/Core/AST/ReturnStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 28 "../../../Source/Core/AST/ReturnStmt.nll"
			ReturnStmt pReturnStmt = new ReturnStmt();
#line 30 "../../../Source/Core/AST/ReturnStmt.nll"
			pReturnStmt.m_pFirstToken = pReturnToken;
#line 31 "../../../Source/Core/AST/ReturnStmt.nll"
			pReturnStmt.m_pExpression = pExpression;
#line 33 "../../../Source/Core/AST/ReturnStmt.nll"
			if (pExpression != null)
			{
				NumbatLogic.AST __1929399913 = pExpression;
#line 34 "../../../Source/Core/AST/ReturnStmt.nll"
				pExpression = null;
#line 34 "../../../Source/Core/AST/ReturnStmt.nll"
				pReturnStmt.AddChild(__1929399913);
			}
#line 36 "../../../Source/Core/AST/ReturnStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ReturnStmt __2739522412 = pReturnStmt;
#line 37 "../../../Source/Core/AST/ReturnStmt.nll"
			pReturnStmt = null;
#line 37 "../../../Source/Core/AST/ReturnStmt.nll"
			return __2739522412;
		}

#line 40 "../../../Source/Core/AST/ReturnStmt.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 42 "../../../Source/Core/AST/ReturnStmt.nll"
			base.Validate(pValidator, pParent);
#line 43 "../../../Source/Core/AST/ReturnStmt.nll"
			pValidator.InjectCleanup(this);
		}

#line 46 "../../../Source/Core/AST/ReturnStmt.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 48 "../../../Source/Core/AST/ReturnStmt.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 49 "../../../Source/Core/AST/ReturnStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 51 "../../../Source/Core/AST/ReturnStmt.nll"
			pOutputBuilder.m_sOut.AppendString("return");
#line 52 "../../../Source/Core/AST/ReturnStmt.nll"
			if (m_pExpression != null)
			{
#line 54 "../../../Source/Core/AST/ReturnStmt.nll"
				pOutputBuilder.m_sOut.AppendChar(' ');
#line 55 "../../../Source/Core/AST/ReturnStmt.nll"
				m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
#line 57 "../../../Source/Core/AST/ReturnStmt.nll"
			pOutputBuilder.m_sOut.AppendString(";\n");
		}

	}
}

