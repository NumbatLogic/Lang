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
			Token pBreakToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CONTINUE);
			if (pBreakToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
				Console.Log("expected semicolon");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			ContinueStmt pContinueStmt = new ContinueStmt();
			pContinueStmt.m_eType = AST.Type.AST_CONTINUE_STMT;
			pContinueStmt.m_pFirstToken = pBreakToken;
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ContinueStmt __2497879999 = pContinueStmt;
			pContinueStmt = null;
			return __2497879999;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			pValidator.InjectCleanup(this);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			Util.Pad(nDepth, sOut);
			sOut.Append("continue;\n");
		}

	}
}

