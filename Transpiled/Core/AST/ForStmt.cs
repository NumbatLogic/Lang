namespace NumbatLogic
{
	class ForStmt : AST
	{
		public ForStmt()
		{
			m_eType = AST.Type.AST_FOR_STMT;
			m_bStatement = true;
		}

		public static ForStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pForToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_FOR);
			if (pForToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
				Console.Log("expected left paren");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pBeforeStatement = VarDecl.TryCreate(pTokenContainer, pTempOffset, true);
			if (pBeforeStatement == null)
			{
				pBeforeStatement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pBeforeStatement == null)
				{
					Console.Log("expected before statement");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
				Console.Log("expected semicolon");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pConditionStatement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pConditionStatement == null)
			{
				Console.Log("expected condition statement");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
				Console.Log("expected semicolon");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pLoopStatement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) == null)
			{
				Console.Log("expected right paren");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pStatement = Scope.TryCreate(pTokenContainer, pTempOffset, true);
			if (pStatement == null)
			{
				Console.Log("expected statement / scope");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
			}
			ForStmt pForStmt = new ForStmt();
			pForStmt.m_pFirstToken = pForToken;
			NumbatLogic.AST __2156020446 = pBeforeStatement;
			pBeforeStatement = null;
			pForStmt.AddChild(__2156020446);
			NumbatLogic.AST __764111395 = pConditionStatement;
			pConditionStatement = null;
			pForStmt.AddChild(__764111395);
			if (pLoopStatement != null)
			{
				NumbatLogic.AST __373112406 = pLoopStatement;
				pLoopStatement = null;
				pForStmt.AddChild(__373112406);
			}
			NumbatLogic.AST __3036777715 = pStatement;
			pStatement = null;
			pForStmt.AddChild(__3036777715);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ForStmt __464585012 = pForStmt;
			pForStmt = null;
			return __464585012;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			AST pBeforeStatement = m_pFirstChild;
			AST pConditionStatement = pBeforeStatement.m_pNextSibling;
			AST pLoopStatement = pConditionStatement.m_pNextSibling;
			AST pStatement = pLoopStatement.m_pNextSibling;
			Util.Pad(nDepth, sOut);
			sOut.Append("for (");
			pBeforeStatement.Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut.Append("; ");
			pConditionStatement.Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut.Append("; ");
			if (pStatement != null)
				pLoopStatement.Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut.Append(")\n");
			if (pStatement == null)
				pStatement = pLoopStatement;
			pStatement.Stringify(eLanguage, eOutputFile, nDepth, sOut);
		}

	}
}

