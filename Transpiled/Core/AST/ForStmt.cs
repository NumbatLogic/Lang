#line 1 "../../../Source/Core/AST/ForStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ForStmt.nll"
	class ForStmt : AST
	{
#line 5 "../../../Source/Core/AST/ForStmt.nll"
		public ForStmt()
		{
#line 7 "../../../Source/Core/AST/ForStmt.nll"
			m_eType = AST.Type.AST_FOR_STMT;
#line 8 "../../../Source/Core/AST/ForStmt.nll"
			m_bStatement = true;
		}

#line 11 "../../../Source/Core/AST/ForStmt.nll"
		public static ForStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 13 "../../../Source/Core/AST/ForStmt.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 15 "../../../Source/Core/AST/ForStmt.nll"
			Token pForToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_FOR);
#line 16 "../../../Source/Core/AST/ForStmt.nll"
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
#line 22 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log("expected left paren");
#line 23 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 24 "../../../Source/Core/AST/ForStmt.nll"
				return null;
			}
#line 26 "../../../Source/Core/AST/ForStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 28 "../../../Source/Core/AST/ForStmt.nll"
			AST pBeforeStatement = VarDecl.TryCreate(pTokenContainer, pTempOffset, true);
#line 29 "../../../Source/Core/AST/ForStmt.nll"
			if (pBeforeStatement == null)
			{
#line 31 "../../../Source/Core/AST/ForStmt.nll"
				pBeforeStatement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 32 "../../../Source/Core/AST/ForStmt.nll"
				if (pBeforeStatement == null)
				{
#line 34 "../../../Source/Core/AST/ForStmt.nll"
					Console.Log("expected before statement");
#line 35 "../../../Source/Core/AST/ForStmt.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 36 "../../../Source/Core/AST/ForStmt.nll"
					NumbatLogic.Assert.Plz(false);
#line 37 "../../../Source/Core/AST/ForStmt.nll"
					return null;
				}
			}
#line 41 "../../../Source/Core/AST/ForStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
#line 43 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log("expected semicolon");
#line 44 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 45 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 46 "../../../Source/Core/AST/ForStmt.nll"
				return null;
			}
#line 48 "../../../Source/Core/AST/ForStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 50 "../../../Source/Core/AST/ForStmt.nll"
			AST pConditionStatement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 51 "../../../Source/Core/AST/ForStmt.nll"
			if (pConditionStatement == null)
			{
#line 53 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log("expected condition statement");
#line 54 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 55 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 56 "../../../Source/Core/AST/ForStmt.nll"
				return null;
			}
#line 59 "../../../Source/Core/AST/ForStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
#line 61 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log("expected semicolon");
#line 62 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 63 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 64 "../../../Source/Core/AST/ForStmt.nll"
				return null;
			}
#line 66 "../../../Source/Core/AST/ForStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 68 "../../../Source/Core/AST/ForStmt.nll"
			AST pLoopStatement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 77 "../../../Source/Core/AST/ForStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) == null)
			{
#line 79 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log("expected right paren");
#line 80 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 81 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 82 "../../../Source/Core/AST/ForStmt.nll"
				return null;
			}
#line 84 "../../../Source/Core/AST/ForStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 86 "../../../Source/Core/AST/ForStmt.nll"
			AST pStatement = Scope.TryCreate(pTokenContainer, pTempOffset, true);
#line 87 "../../../Source/Core/AST/ForStmt.nll"
			if (pStatement == null)
			{
#line 89 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log("expected statement / scope");
#line 90 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 91 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic.Assert.Plz(false);
			}
#line 94 "../../../Source/Core/AST/ForStmt.nll"
			ForStmt pForStmt = new ForStmt();
#line 95 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt.m_pFirstToken = pForToken;
			NumbatLogic.AST __2156020446 = pBeforeStatement;
#line 97 "../../../Source/Core/AST/ForStmt.nll"
			pBeforeStatement = null;
#line 97 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt.AddChild(__2156020446);
			NumbatLogic.AST __764111395 = pConditionStatement;
#line 98 "../../../Source/Core/AST/ForStmt.nll"
			pConditionStatement = null;
#line 98 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt.AddChild(__764111395);
#line 99 "../../../Source/Core/AST/ForStmt.nll"
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

#line 107 "../../../Source/Core/AST/ForStmt.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 109 "../../../Source/Core/AST/ForStmt.nll"
			AST pBeforeStatement = m_pFirstChild;
#line 110 "../../../Source/Core/AST/ForStmt.nll"
			AST pConditionStatement = pBeforeStatement.m_pNextSibling;
#line 111 "../../../Source/Core/AST/ForStmt.nll"
			AST pLoopStatement = pConditionStatement.m_pNextSibling;
#line 112 "../../../Source/Core/AST/ForStmt.nll"
			AST pStatement = pLoopStatement.m_pNextSibling;
#line 114 "../../../Source/Core/AST/ForStmt.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 116 "../../../Source/Core/AST/ForStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 117 "../../../Source/Core/AST/ForStmt.nll"
			pOutputBuilder.m_sOut.Append("for (");
#line 118 "../../../Source/Core/AST/ForStmt.nll"
			pBeforeStatement.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 119 "../../../Source/Core/AST/ForStmt.nll"
			pOutputBuilder.m_sOut.Append("; ");
#line 120 "../../../Source/Core/AST/ForStmt.nll"
			pConditionStatement.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 121 "../../../Source/Core/AST/ForStmt.nll"
			pOutputBuilder.m_sOut.Append("; ");
#line 123 "../../../Source/Core/AST/ForStmt.nll"
			if (pStatement != null)
#line 124 "../../../Source/Core/AST/ForStmt.nll"
				pLoopStatement.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 126 "../../../Source/Core/AST/ForStmt.nll"
			pOutputBuilder.m_sOut.Append(")\n");
#line 128 "../../../Source/Core/AST/ForStmt.nll"
			if (pStatement == null)
#line 129 "../../../Source/Core/AST/ForStmt.nll"
				pStatement = pLoopStatement;
#line 131 "../../../Source/Core/AST/ForStmt.nll"
			pStatement.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		}

	}
}

