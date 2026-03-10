#line 1 "../../../Source/Core/AST/BreakStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/BreakStmt.nll"
	class BreakStmt : AST
	{
#line 5 "../../../Source/Core/AST/BreakStmt.nll"
		public BreakStmt()
		{
#line 7 "../../../Source/Core/AST/BreakStmt.nll"
			m_bStatement = true;
		}

#line 10 "../../../Source/Core/AST/BreakStmt.nll"
		public static BreakStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 12 "../../../Source/Core/AST/BreakStmt.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 14 "../../../Source/Core/AST/BreakStmt.nll"
			Token pBreakToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_BREAK);
#line 15 "../../../Source/Core/AST/BreakStmt.nll"
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
#line 21 "../../../Source/Core/AST/BreakStmt.nll"
				Console.Log("expected semicolon");
#line 22 "../../../Source/Core/AST/BreakStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 23 "../../../Source/Core/AST/BreakStmt.nll"
				return null;
			}
#line 25 "../../../Source/Core/AST/BreakStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 27 "../../../Source/Core/AST/BreakStmt.nll"
			BreakStmt pBreakStmt = new BreakStmt();
#line 29 "../../../Source/Core/AST/BreakStmt.nll"
			pBreakStmt.m_eType = AST.Type.AST_BREAK_STMT;
#line 30 "../../../Source/Core/AST/BreakStmt.nll"
			pBreakStmt.m_pFirstToken = pBreakToken;
#line 32 "../../../Source/Core/AST/BreakStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.BreakStmt __3206362871 = pBreakStmt;
#line 33 "../../../Source/Core/AST/BreakStmt.nll"
			pBreakStmt = null;
#line 33 "../../../Source/Core/AST/BreakStmt.nll"
			return __3206362871;
		}

#line 36 "../../../Source/Core/AST/BreakStmt.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 38 "../../../Source/Core/AST/BreakStmt.nll"
			base.Validate(pValidator, pParent);
#line 39 "../../../Source/Core/AST/BreakStmt.nll"
			pValidator.InjectCleanup(this);
		}

#line 42 "../../../Source/Core/AST/BreakStmt.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 44 "../../../Source/Core/AST/BreakStmt.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 46 "../../../Source/Core/AST/BreakStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 47 "../../../Source/Core/AST/BreakStmt.nll"
			pOutputBuilder.m_sOut.Append("break;\n");
		}

	}
}

