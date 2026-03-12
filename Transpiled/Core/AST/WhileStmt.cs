#line 1 "../../../Source/Core/AST/WhileStmt.nll"
namespace NumbatLogic
{
	class WhileStmt : AST
	{
		public AST m_pExpression;
		public Scope m_pScope;
#line 8 "../../../Source/Core/AST/WhileStmt.nll"
		public WhileStmt()
		{
			m_bStatement = true;
		}

		public static WhileStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/WhileStmt.nll"
			Token pWhileToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_WHILE);
			if (pWhileToken == null)
			{
#line 19 "../../../Source/Core/AST/WhileStmt.nll"
				return null;
			}
#line 20 "../../../Source/Core/AST/WhileStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 22 "../../../Source/Core/AST/WhileStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
				Console.Log("expected left paren");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 30 "../../../Source/Core/AST/WhileStmt.nll"
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
				Console.Log("expected expression");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
#line 38 "../../../Source/Core/AST/WhileStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) == null)
			{
				Console.Log("expected right paren");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 47 "../../../Source/Core/AST/WhileStmt.nll"
			Scope pScope = Scope.TryCreate(pTokenContainer, pTempOffset, true);
			if (pScope == null)
			{
				Console.Log("expected scope");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
			}
#line 55 "../../../Source/Core/AST/WhileStmt.nll"
			WhileStmt pWhileStmt = new WhileStmt();
#line 57 "../../../Source/Core/AST/WhileStmt.nll"
			pWhileStmt.m_eType = AST.Type.AST_WHILE_STMT;
			pWhileStmt.m_pFirstToken = pWhileToken;
			pWhileStmt.m_pExpression = pExpression;
			pWhileStmt.m_pScope = pScope;
			NumbatLogic.AST __1929596708 = pExpression;
			pExpression = null;
#line 62 "../../../Source/Core/AST/WhileStmt.nll"
			pWhileStmt.AddChild(__1929596708);
			NumbatLogic.Scope __1530749729 = pScope;
#line 63 "../../../Source/Core/AST/WhileStmt.nll"
			pScope = null;
#line 63 "../../../Source/Core/AST/WhileStmt.nll"
			pWhileStmt.AddChild(__1530749729);
#line 65 "../../../Source/Core/AST/WhileStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.WhileStmt __2238546185 = pWhileStmt;
#line 66 "../../../Source/Core/AST/WhileStmt.nll"
			pWhileStmt = null;
#line 66 "../../../Source/Core/AST/WhileStmt.nll"
			return __2238546185;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 74 "../../../Source/Core/AST/WhileStmt.nll"
			pOutputBuilder.m_sOut.Append("while (");
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder.m_sOut.Append(")\n");
			m_pScope.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		}

	}
}

