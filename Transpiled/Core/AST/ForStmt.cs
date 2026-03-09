#line 1 "../../../Source/Core/AST/ForStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/ForStmt.nll"
	class ForStmt : AST
	{
#line 6 "../../../Source/Core/AST/ForStmt.nll"
		public ForStmt()
		{
#line 8 "../../../Source/Core/AST/ForStmt.nll"
			m_eType = AST.Type.AST_FOR_STMT;
#line 9 "../../../Source/Core/AST/ForStmt.nll"
			m_bStatement = true;
		}

#line 12 "../../../Source/Core/AST/ForStmt.nll"
		public static ForStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pForToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_FOR);
#line 17 "../../../Source/Core/AST/ForStmt.nll"
			if (pForToken == null)
			{
#line 18 "../../../Source/Core/AST/ForStmt.nll"
				return null;
			}
#line 19 "../../../Source/Core/AST/ForStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 21 "../../../Source/Core/AST/ForStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
#line 23 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log("expected left paren");
#line 24 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 25 "../../../Source/Core/AST/ForStmt.nll"
				return null;
			}
#line 27 "../../../Source/Core/AST/ForStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pBeforeStatement = VarDecl.TryCreate(pTokenContainer, pTempOffset, true);
#line 30 "../../../Source/Core/AST/ForStmt.nll"
			if (pBeforeStatement == null)
			{
#line 32 "../../../Source/Core/AST/ForStmt.nll"
				pBeforeStatement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 33 "../../../Source/Core/AST/ForStmt.nll"
				if (pBeforeStatement == null)
				{
#line 35 "../../../Source/Core/AST/ForStmt.nll"
					Console.Log("expected before statement");
#line 36 "../../../Source/Core/AST/ForStmt.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 37 "../../../Source/Core/AST/ForStmt.nll"
					NumbatLogic.Assert.Plz(false);
#line 38 "../../../Source/Core/AST/ForStmt.nll"
					return null;
				}
			}
#line 42 "../../../Source/Core/AST/ForStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
#line 44 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log("expected semicolon");
#line 45 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 46 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 47 "../../../Source/Core/AST/ForStmt.nll"
				return null;
			}
#line 49 "../../../Source/Core/AST/ForStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pConditionStatement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 52 "../../../Source/Core/AST/ForStmt.nll"
			if (pConditionStatement == null)
			{
#line 54 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log("expected condition statement");
#line 55 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 56 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 57 "../../../Source/Core/AST/ForStmt.nll"
				return null;
			}
#line 60 "../../../Source/Core/AST/ForStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
#line 62 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log("expected semicolon");
#line 63 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 64 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 65 "../../../Source/Core/AST/ForStmt.nll"
				return null;
			}
#line 67 "../../../Source/Core/AST/ForStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pLoopStatement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 78 "../../../Source/Core/AST/ForStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) == null)
			{
#line 80 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log("expected right paren");
#line 81 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 82 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 83 "../../../Source/Core/AST/ForStmt.nll"
				return null;
			}
#line 85 "../../../Source/Core/AST/ForStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pStatement = Scope.TryCreate(pTokenContainer, pTempOffset, true);
#line 88 "../../../Source/Core/AST/ForStmt.nll"
			if (pStatement == null)
			{
#line 90 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log("expected statement / scope");
#line 91 "../../../Source/Core/AST/ForStmt.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 92 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic.Assert.Plz(false);
			}
			ForStmt pForStmt = new ForStmt();
#line 96 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt.m_pFirstToken = pForToken;
			NumbatLogic.AST __2156020446 = pBeforeStatement;
#line 98 "../../../Source/Core/AST/ForStmt.nll"
			pBeforeStatement = null;
#line 98 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt.AddChild(__2156020446);
			NumbatLogic.AST __764111395 = pConditionStatement;
#line 99 "../../../Source/Core/AST/ForStmt.nll"
			pConditionStatement = null;
#line 99 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt.AddChild(__764111395);
#line 100 "../../../Source/Core/AST/ForStmt.nll"
			if (pLoopStatement != null)
			{
				NumbatLogic.AST __373112406 = pLoopStatement;
#line 101 "../../../Source/Core/AST/ForStmt.nll"
				pLoopStatement = null;
#line 101 "../../../Source/Core/AST/ForStmt.nll"
				pForStmt.AddChild(__373112406);
			}
			NumbatLogic.AST __3036777715 = pStatement;
#line 102 "../../../Source/Core/AST/ForStmt.nll"
			pStatement = null;
#line 102 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt.AddChild(__3036777715);
#line 104 "../../../Source/Core/AST/ForStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ForStmt __464585012 = pForStmt;
#line 105 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt = null;
#line 105 "../../../Source/Core/AST/ForStmt.nll"
			return __464585012;
		}

#line 108 "../../../Source/Core/AST/ForStmt.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			AST pBeforeStatement = m_pFirstChild;
			AST pConditionStatement = pBeforeStatement.m_pNextSibling;
			AST pLoopStatement = pConditionStatement.m_pNextSibling;
			AST pStatement = pLoopStatement.m_pNextSibling;
#line 115 "../../../Source/Core/AST/ForStmt.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 117 "../../../Source/Core/AST/ForStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 118 "../../../Source/Core/AST/ForStmt.nll"
			pOutputBuilder.m_sOut.Append("for (");
#line 119 "../../../Source/Core/AST/ForStmt.nll"
			pBeforeStatement.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 120 "../../../Source/Core/AST/ForStmt.nll"
			pOutputBuilder.m_sOut.Append("; ");
#line 121 "../../../Source/Core/AST/ForStmt.nll"
			pConditionStatement.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 122 "../../../Source/Core/AST/ForStmt.nll"
			pOutputBuilder.m_sOut.Append("; ");
#line 124 "../../../Source/Core/AST/ForStmt.nll"
			if (pStatement != null)
#line 125 "../../../Source/Core/AST/ForStmt.nll"
				pLoopStatement.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 127 "../../../Source/Core/AST/ForStmt.nll"
			pOutputBuilder.m_sOut.Append(")\n");
#line 129 "../../../Source/Core/AST/ForStmt.nll"
			if (pStatement == null)
#line 130 "../../../Source/Core/AST/ForStmt.nll"
				pStatement = pLoopStatement;
#line 132 "../../../Source/Core/AST/ForStmt.nll"
			pStatement.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		}

	}
}

