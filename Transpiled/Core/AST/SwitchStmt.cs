#line 1 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
namespace NumbatLogic
{
	class SwitchStmt : AST
	{
		public AST m_pExpression;
		public Vector<AST> m_pExpressionVector;
		public Vector<AST> m_pStatementVector;
		public AST m_pDefaultStatement;
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
		public SwitchStmt()
		{
			m_eType = AST.Type.AST_SWITCH_STMT;
			m_bStatement = true;
			m_pExpressionVector = new Vector<AST>();
			m_pStatementVector = new Vector<AST>();
			m_pDefaultStatement = null;
		}

		public static SwitchStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			Token pSwitchToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_SWITCH);
			if (pSwitchToken == null)
			{
#line 25 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				return null;
			}
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 28 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
				Console.Log("expected left paren");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 36 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
				Console.Log("expected expression");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
#line 44 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) == null)
			{
				Console.Log("expected right paren");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
			{
				Console.Log("expected opening curly brace");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 62 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			SwitchStmt pSwitchStmt = new SwitchStmt();
			pSwitchStmt.m_pFirstToken = pSwitchToken;
			pSwitchStmt.m_pExpression = pExpression;
			NumbatLogic.AST __1929596711 = pExpression;
#line 65 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			pExpression = null;
#line 65 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			pSwitchStmt.AddChild(__1929596711);
#line 67 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
#line 75 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				if (pSwitchStmt.m_pDefaultStatement != null)
				{
					Console.Log("expected default to be last thing in switch statement");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
#line 83 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				Token pCaseToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CASE);
				Token pDefaultToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DEFAULT);
				if (pCaseToken == null && pDefaultToken == null)
				{
					Console.Log("expected case or default");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 94 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				if (pDefaultToken != null)
				{
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON) == null)
					{
						Console.Log("expected colon A");
						Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
						NumbatLogic.Assert.Plz(false);
						return null;
					}
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 105 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
					AST pDefaultStatement = AST.CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
					if (pDefaultStatement == null)
					{
						Console.Log("expected case statement");
						Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
						NumbatLogic.Assert.Plz(false);
						return null;
					}
#line 114 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
					AST pScopedDefaultStatement = null;
					if (pDefaultStatement.m_eType == AST.Type.AST_SCOPE)
					{
						NumbatLogic.AST __2021738808 = pDefaultStatement;
#line 116 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
						pDefaultStatement = null;
#line 116 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
						pScopedDefaultStatement = __2021738808;
					}
					else
					{
#line 119 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
						pScopedDefaultStatement = new Scope();
						NumbatLogic.AST __2021804401 = pDefaultStatement;
#line 120 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
						pDefaultStatement = null;
#line 120 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
						pScopedDefaultStatement.AddChild(__2021804401);
					}
#line 123 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
					pSwitchStmt.m_pDefaultStatement = pScopedDefaultStatement;
					NumbatLogic.AST __4074538021 = pScopedDefaultStatement;
#line 124 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
					pScopedDefaultStatement = null;
#line 124 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
					pSwitchStmt.AddChild(__4074538021);
					continue;
				}
#line 128 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				AST pCaseExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pCaseExpression == null)
				{
					Console.Log("expected case expression");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
				pSwitchStmt.m_pExpressionVector.PushBack(pCaseExpression);
				NumbatLogic.AST __155144765 = pCaseExpression;
#line 137 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				pCaseExpression = null;
#line 137 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				pSwitchStmt.AddChild(__155144765);
#line 140 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON) == null)
				{
					Console.Log("expected colon B");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 149 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CASE) != null)
				{
					pSwitchStmt.m_pStatementVector.PushBack(null);
					continue;
				}
#line 155 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				AST pCaseStatement = AST.CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
				if (pCaseStatement == null)
				{
					Console.Log("expected case statement");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
#line 164 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				AST pScopedCaseStatement = null;
				if (pCaseStatement.m_eType == AST.Type.AST_SCOPE)
				{
					NumbatLogic.AST __2964786434 = pCaseStatement;
#line 166 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
					pCaseStatement = null;
#line 166 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
					pScopedCaseStatement = __2964786434;
				}
				else
				{
#line 169 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
					pScopedCaseStatement = new Scope();
					NumbatLogic.AST __2964852027 = pCaseStatement;
#line 170 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
					pCaseStatement = null;
#line 170 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
					pScopedCaseStatement.AddChild(__2964852027);
				}
#line 173 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				pSwitchStmt.m_pStatementVector.PushBack(pScopedCaseStatement);
				NumbatLogic.AST __1629474447 = pScopedCaseStatement;
#line 174 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				pScopedCaseStatement = null;
#line 174 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				pSwitchStmt.AddChild(__1629474447);
			}
#line 177 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.SwitchStmt __1732082662 = pSwitchStmt;
#line 178 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			pSwitchStmt = null;
#line 178 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			return __1732082662;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 186 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			pOutputBuilder.m_sOut.Append("switch (");
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder.m_sOut.Append(")\n");
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
			pOutputBuilder.m_sOut.Append("{\n");
			nDepth++;
			for (int i = 0; i < m_pExpressionVector.GetSize(); i++)
			{
				AST pCaseExpression = m_pExpressionVector.Get(i);
				AST pCaseStatement = m_pStatementVector.Get(i);
#line 197 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
				pOutputBuilder.m_sOut.Append("case ");
				pCaseExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				pOutputBuilder.m_sOut.Append(":\n");
				if (pCaseStatement != null)
				{
					pCaseStatement.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
					pOutputBuilder.m_sOut.Append("\n");
				}
			}
#line 208 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			if (m_pDefaultStatement != null)
			{
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
				pOutputBuilder.m_sOut.Append("default:\n");
				m_pDefaultStatement.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
				pOutputBuilder.m_sOut.Append("\n");
			}
#line 216 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
			nDepth--;
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
			pOutputBuilder.m_sOut.AppendString("}\n");
		}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
		~SwitchStmt()
		{
		}

	}
}

