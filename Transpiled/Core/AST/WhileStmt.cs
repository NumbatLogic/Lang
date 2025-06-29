namespace NumbatLogic
{
	class WhileStmt : AST
	{
		public AST m_pExpression;
		public Scope m_pScope;
		public WhileStmt()
		{
			m_bStatement = true;
		}

		public static WhileStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pWhileToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_WHILE);
			if (pWhileToken == null)
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
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
				Console.Log("expected expression");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) == null)
			{
				Console.Log("expected right paren");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			Scope pScope = Scope.TryCreate(pTokenContainer, pTempOffset, true);
			if (pScope == null)
			{
				Console.Log("expected scope");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
			}
			WhileStmt pWhileStmt = new WhileStmt();
			pWhileStmt.m_eType = AST.Type.AST_WHILE_STMT;
			pWhileStmt.m_pFirstToken = pWhileToken;
			pWhileStmt.m_pExpression = pExpression;
			pWhileStmt.m_pScope = pScope;
			NumbatLogic.AST __1233045057 = pExpression;
			pExpression = null;
			pWhileStmt.AddChild(__1233045057);
			NumbatLogic.Scope __4281081568 = pScope;
			pScope = null;
			pWhileStmt.AddChild(__4281081568);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.WhileStmt __1903884803 = pWhileStmt;
			pWhileStmt = null;
			return __1903884803;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			Util.Pad(nDepth, sOut);
			sOut.Append("while (");
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut.Append(")\n");
			m_pScope.Stringify(eLanguage, eOutputFile, nDepth, sOut);
		}

	}
}

