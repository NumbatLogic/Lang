#line 1 "../../../Source/Core/AST/ContinueStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ContinueStmt.nll"
	class ContinueStmt : AST
	{
#line 5 "../../../Source/Core/AST/ContinueStmt.nll"
		public ContinueStmt()
		{
#line 7 "../../../Source/Core/AST/ContinueStmt.nll"
			m_bStatement = true;
		}

#line 10 "../../../Source/Core/AST/ContinueStmt.nll"
		public static ContinueStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 12 "../../../Source/Core/AST/ContinueStmt.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 14 "../../../Source/Core/AST/ContinueStmt.nll"
			Token pBreakToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CONTINUE);
#line 15 "../../../Source/Core/AST/ContinueStmt.nll"
			if (pBreakToken == null)
			{
#line 16 "../../../Source/Core/AST/ContinueStmt.nll"
				return null;
			}
#line 17 "../../../Source/Core/AST/ContinueStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 19 "../../../Source/Core/AST/ContinueStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
#line 21 "../../../Source/Core/AST/ContinueStmt.nll"
				Console.Log("expected semicolon");
#line 22 "../../../Source/Core/AST/ContinueStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 23 "../../../Source/Core/AST/ContinueStmt.nll"
				return null;
			}
#line 25 "../../../Source/Core/AST/ContinueStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 27 "../../../Source/Core/AST/ContinueStmt.nll"
			ContinueStmt pContinueStmt = new ContinueStmt();
#line 29 "../../../Source/Core/AST/ContinueStmt.nll"
			pContinueStmt.m_eType = AST.Type.AST_CONTINUE_STMT;
#line 30 "../../../Source/Core/AST/ContinueStmt.nll"
			pContinueStmt.m_pFirstToken = pBreakToken;
#line 32 "../../../Source/Core/AST/ContinueStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ContinueStmt __2497879999 = pContinueStmt;
#line 33 "../../../Source/Core/AST/ContinueStmt.nll"
			pContinueStmt = null;
#line 33 "../../../Source/Core/AST/ContinueStmt.nll"
			return __2497879999;
		}

#line 36 "../../../Source/Core/AST/ContinueStmt.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 38 "../../../Source/Core/AST/ContinueStmt.nll"
			base.Validate(pValidator, pParent);
#line 39 "../../../Source/Core/AST/ContinueStmt.nll"
			pValidator.InjectCleanup(this);
		}

#line 42 "../../../Source/Core/AST/ContinueStmt.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 44 "../../../Source/Core/AST/ContinueStmt.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 45 "../../../Source/Core/AST/ContinueStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 46 "../../../Source/Core/AST/ContinueStmt.nll"
			pOutputBuilder.m_sOut.Append("continue;\n");
		}

	}
}

