#line 1 "../../../Source/Core/AST/ContinueStmt.nll"
namespace NumbatLogic
{
	class ContinueStmt : AST
	{
		public ContinueStmt()
		{
			m_bStatement = true;
		}

		public static ContinueStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 14 "../../../Source/Core/AST/ContinueStmt.nll"
			Token pBreakToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CONTINUE);
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
				Console.Log("expected semicolon");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 27 "../../../Source/Core/AST/ContinueStmt.nll"
			ContinueStmt pContinueStmt = new ContinueStmt();
#line 29 "../../../Source/Core/AST/ContinueStmt.nll"
			pContinueStmt.m_eType = AST.Type.AST_CONTINUE_STMT;
			pContinueStmt.m_pFirstToken = pBreakToken;
#line 32 "../../../Source/Core/AST/ContinueStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ContinueStmt __2497879999 = pContinueStmt;
#line 33 "../../../Source/Core/AST/ContinueStmt.nll"
			pContinueStmt = null;
#line 33 "../../../Source/Core/AST/ContinueStmt.nll"
			return __2497879999;
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
			pOutputBuilder.m_sOut.Append("continue;\n");
		}

	}
}

