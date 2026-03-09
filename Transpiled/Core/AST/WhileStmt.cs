#line 1 "../../../Source/Core/AST/WhileStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/WhileStmt.nll"
	class WhileStmt : AST
	{
#line 6 "../../../Source/Core/AST/WhileStmt.nll"
		public AST m_pExpression;
#line 7 "../../../Source/Core/AST/WhileStmt.nll"
		public Scope m_pScope;
#line 9 "../../../Source/Core/AST/WhileStmt.nll"
		public WhileStmt()
		{
#line 11 "../../../Source/Core/AST/WhileStmt.nll"
			m_bStatement = true;
		}

#line 14 "../../../Source/Core/AST/WhileStmt.nll"
		public static WhileStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pWhileToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_WHILE);
#line 19 "../../../Source/Core/AST/WhileStmt.nll"
			if (pWhileToken == null)
			{
#line 20 "../../../Source/Core/AST/WhileStmt.nll"
				return null;
			}
#line 21 "../../../Source/Core/AST/WhileStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 23 "../../../Source/Core/AST/WhileStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
#line 25 "../../../Source/Core/AST/WhileStmt.nll"
				Console.Log("expected left paren");
#line 26 "../../../Source/Core/AST/WhileStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 27 "../../../Source/Core/AST/WhileStmt.nll"
				return null;
			}
#line 29 "../../../Source/Core/AST/WhileStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 32 "../../../Source/Core/AST/WhileStmt.nll"
			if (pExpression == null)
			{
#line 34 "../../../Source/Core/AST/WhileStmt.nll"
				Console.Log("expected expression");
#line 35 "../../../Source/Core/AST/WhileStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 36 "../../../Source/Core/AST/WhileStmt.nll"
				return null;
			}
#line 39 "../../../Source/Core/AST/WhileStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) == null)
			{
#line 41 "../../../Source/Core/AST/WhileStmt.nll"
				Console.Log("expected right paren");
#line 42 "../../../Source/Core/AST/WhileStmt.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 43 "../../../Source/Core/AST/WhileStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 44 "../../../Source/Core/AST/WhileStmt.nll"
				return null;
			}
#line 46 "../../../Source/Core/AST/WhileStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			Scope pScope = Scope.TryCreate(pTokenContainer, pTempOffset, true);
#line 49 "../../../Source/Core/AST/WhileStmt.nll"
			if (pScope == null)
			{
#line 51 "../../../Source/Core/AST/WhileStmt.nll"
				Console.Log("expected scope");
#line 52 "../../../Source/Core/AST/WhileStmt.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 53 "../../../Source/Core/AST/WhileStmt.nll"
				NumbatLogic.Assert.Plz(false);
			}
			WhileStmt pWhileStmt = new WhileStmt();
#line 58 "../../../Source/Core/AST/WhileStmt.nll"
			pWhileStmt.m_eType = AST.Type.AST_WHILE_STMT;
#line 59 "../../../Source/Core/AST/WhileStmt.nll"
			pWhileStmt.m_pFirstToken = pWhileToken;
#line 60 "../../../Source/Core/AST/WhileStmt.nll"
			pWhileStmt.m_pExpression = pExpression;
#line 61 "../../../Source/Core/AST/WhileStmt.nll"
			pWhileStmt.m_pScope = pScope;
			NumbatLogic.AST __1929596708 = pExpression;
#line 63 "../../../Source/Core/AST/WhileStmt.nll"
			pExpression = null;
#line 63 "../../../Source/Core/AST/WhileStmt.nll"
			pWhileStmt.AddChild(__1929596708);
			NumbatLogic.Scope __1530749729 = pScope;
#line 64 "../../../Source/Core/AST/WhileStmt.nll"
			pScope = null;
#line 64 "../../../Source/Core/AST/WhileStmt.nll"
			pWhileStmt.AddChild(__1530749729);
#line 66 "../../../Source/Core/AST/WhileStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.WhileStmt __2238546185 = pWhileStmt;
#line 67 "../../../Source/Core/AST/WhileStmt.nll"
			pWhileStmt = null;
#line 67 "../../../Source/Core/AST/WhileStmt.nll"
			return __2238546185;
		}

#line 70 "../../../Source/Core/AST/WhileStmt.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 72 "../../../Source/Core/AST/WhileStmt.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 73 "../../../Source/Core/AST/WhileStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 75 "../../../Source/Core/AST/WhileStmt.nll"
			pOutputBuilder.m_sOut.Append("while (");
#line 76 "../../../Source/Core/AST/WhileStmt.nll"
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 77 "../../../Source/Core/AST/WhileStmt.nll"
			pOutputBuilder.m_sOut.Append(")\n");
#line 78 "../../../Source/Core/AST/WhileStmt.nll"
			m_pScope.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		}

	}
}

