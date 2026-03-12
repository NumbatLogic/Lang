#line 1 "../../../Source/Core/AST/ForStmt.nll"
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
#line 15 "../../../Source/Core/AST/ForStmt.nll"
			Token pForToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_FOR);
			if (pForToken == null)
			{
#line 17 "../../../Source/Core/AST/ForStmt.nll"
				return null;
			}
#line 18 "../../../Source/Core/AST/ForStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 20 "../../../Source/Core/AST/ForStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
				Console.Log("expected left paren");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 28 "../../../Source/Core/AST/ForStmt.nll"
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
#line 41 "../../../Source/Core/AST/ForStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
				Console.Log("expected semicolon");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 50 "../../../Source/Core/AST/ForStmt.nll"
			AST pConditionStatement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pConditionStatement == null)
			{
				Console.Log("expected condition statement");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
#line 59 "../../../Source/Core/AST/ForStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
				Console.Log("expected semicolon");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 68 "../../../Source/Core/AST/ForStmt.nll"
			AST pLoopStatement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 77 "../../../Source/Core/AST/ForStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) == null)
			{
				Console.Log("expected right paren");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 86 "../../../Source/Core/AST/ForStmt.nll"
			AST pStatement = Scope.TryCreate(pTokenContainer, pTempOffset, true);
			if (pStatement == null)
			{
				Console.Log("expected statement / scope");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
			}
#line 94 "../../../Source/Core/AST/ForStmt.nll"
			ForStmt pForStmt = new ForStmt();
			pForStmt.m_pFirstToken = pForToken;
			NumbatLogic.AST __2156020446 = pBeforeStatement;
			pBeforeStatement = null;
#line 97 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt.AddChild(__2156020446);
			NumbatLogic.AST __764111395 = pConditionStatement;
#line 98 "../../../Source/Core/AST/ForStmt.nll"
			pConditionStatement = null;
#line 98 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt.AddChild(__764111395);
			if (pLoopStatement != null)
			{
				NumbatLogic.AST __373112406 = pLoopStatement;
#line 100 "../../../Source/Core/AST/ForStmt.nll"
				pLoopStatement = null;
#line 100 "../../../Source/Core/AST/ForStmt.nll"
				pForStmt.AddChild(__373112406);
			}
			NumbatLogic.AST __3036777715 = pStatement;
#line 101 "../../../Source/Core/AST/ForStmt.nll"
			pStatement = null;
#line 101 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt.AddChild(__3036777715);
#line 103 "../../../Source/Core/AST/ForStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ForStmt __464585012 = pForStmt;
#line 104 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt = null;
#line 104 "../../../Source/Core/AST/ForStmt.nll"
			return __464585012;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			AST pBeforeStatement = m_pFirstChild;
			AST pConditionStatement = pBeforeStatement.m_pNextSibling;
			AST pLoopStatement = pConditionStatement.m_pNextSibling;
			AST pStatement = pLoopStatement.m_pNextSibling;
#line 114 "../../../Source/Core/AST/ForStmt.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 116 "../../../Source/Core/AST/ForStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
			pOutputBuilder.m_sOut.Append("for (");
			pBeforeStatement.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder.m_sOut.Append("; ");
			pConditionStatement.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder.m_sOut.Append("; ");
#line 123 "../../../Source/Core/AST/ForStmt.nll"
			if (pStatement != null)
				pLoopStatement.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 126 "../../../Source/Core/AST/ForStmt.nll"
			pOutputBuilder.m_sOut.Append(")\n");
#line 128 "../../../Source/Core/AST/ForStmt.nll"
			if (pStatement == null)
				pStatement = pLoopStatement;
#line 131 "../../../Source/Core/AST/ForStmt.nll"
			pStatement.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		}

	}
}

