#line 1 "../../../Source/Core/AST/BreakStmt.nll"
namespace NumbatLogic
{
	class BreakStmt : AST
	{
		public BreakStmt()
		{
			m_bStatement = true;
		}

		public static BreakStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 14 "../../../Source/Core/AST/BreakStmt.nll"
			Token pBreakToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_BREAK);
			if (pBreakToken == null)
			{
#line 16 "../../../Source/Core/AST/BreakStmt.nll"
				return null;
			}
#line 17 "../../../Source/Core/AST/BreakStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 19 "../../../Source/Core/AST/BreakStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
				Console.Log("expected semicolon");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 27 "../../../Source/Core/AST/BreakStmt.nll"
			BreakStmt pBreakStmt = new BreakStmt();
#line 29 "../../../Source/Core/AST/BreakStmt.nll"
			pBreakStmt.m_eType = AST.Type.AST_BREAK_STMT;
			pBreakStmt.m_pFirstToken = pBreakToken;
#line 32 "../../../Source/Core/AST/BreakStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.BreakStmt __3206362871 = pBreakStmt;
#line 33 "../../../Source/Core/AST/BreakStmt.nll"
			pBreakStmt = null;
#line 33 "../../../Source/Core/AST/BreakStmt.nll"
			return __3206362871;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			pValidator.InjectCleanup(this);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 46 "../../../Source/Core/AST/BreakStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
			pOutputBuilder.m_sOut.Append("break;\n");
		}

	}
}

