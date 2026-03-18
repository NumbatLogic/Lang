#line 1 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
namespace NumbatLogic
{
	class ReturnStmt : AST
	{
		public AST m_pExpression;
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		public ReturnStmt()
		{
			m_eType = AST.Type.AST_RETURN_STMT;
			m_bStatement = true;
		}

		public static ReturnStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			Token pReturnToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_RETURN);
			if (pReturnToken == null)
			{
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
				return null;
			}
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
#line 25 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
				return null;
			}
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 28 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			ReturnStmt pReturnStmt = new ReturnStmt();
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			pReturnStmt.m_pFirstToken = pReturnToken;
			pReturnStmt.m_pExpression = pExpression;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			if (pExpression != null)
			{
				NumbatLogic.AST __1929399913 = pExpression;
#line 34 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
				pExpression = null;
#line 34 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
				pReturnStmt.AddChild(__1929399913);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ReturnStmt __2739522412 = pReturnStmt;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			pReturnStmt = null;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			return __2739522412;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			pValidator.InjectCleanup(this);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			pOutputBuilder.m_sOut.AppendString("return");
			if (m_pExpression != null)
			{
				pOutputBuilder.m_sOut.AppendChar(' ');
				m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
			pOutputBuilder.m_sOut.AppendString(";\n");
		}

	}
}

