#line 1 "../../../Source/Core/AST/ContinueStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/ContinueStmt.nll"
	class ContinueStmt : AST
	{
#line 6 "../../../Source/Core/AST/ContinueStmt.nll"
		public ContinueStmt()
		{
#line 8 "../../../Source/Core/AST/ContinueStmt.nll"
			m_bStatement = true;
		}

#line 11 "../../../Source/Core/AST/ContinueStmt.nll"
		public static ContinueStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pBreakToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CONTINUE);
#line 16 "../../../Source/Core/AST/ContinueStmt.nll"
			if (pBreakToken == null)
			{
#line 17 "../../../Source/Core/AST/ContinueStmt.nll"
				return null;
			}
#line 18 "../../../Source/Core/AST/ContinueStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 20 "../../../Source/Core/AST/ContinueStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
#line 22 "../../../Source/Core/AST/ContinueStmt.nll"
				Console.Log("expected semicolon");
#line 23 "../../../Source/Core/AST/ContinueStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 24 "../../../Source/Core/AST/ContinueStmt.nll"
				return null;
			}
#line 26 "../../../Source/Core/AST/ContinueStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			ContinueStmt pContinueStmt = new ContinueStmt();
#line 30 "../../../Source/Core/AST/ContinueStmt.nll"
			pContinueStmt.m_eType = AST.Type.AST_CONTINUE_STMT;
#line 31 "../../../Source/Core/AST/ContinueStmt.nll"
			pContinueStmt.m_pFirstToken = pBreakToken;
#line 33 "../../../Source/Core/AST/ContinueStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ContinueStmt __2497879999 = pContinueStmt;
#line 34 "../../../Source/Core/AST/ContinueStmt.nll"
			pContinueStmt = null;
#line 34 "../../../Source/Core/AST/ContinueStmt.nll"
			return __2497879999;
		}

#line 37 "../../../Source/Core/AST/ContinueStmt.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 39 "../../../Source/Core/AST/ContinueStmt.nll"
			base.Validate(pValidator, pParent);
#line 40 "../../../Source/Core/AST/ContinueStmt.nll"
			pValidator.InjectCleanup(this);
		}

#line 43 "../../../Source/Core/AST/ContinueStmt.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 45 "../../../Source/Core/AST/ContinueStmt.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 46 "../../../Source/Core/AST/ContinueStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 47 "../../../Source/Core/AST/ContinueStmt.nll"
			pOutputBuilder.m_sOut.Append("continue;\n");
		}

	}
}

