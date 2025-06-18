namespace NumbatLogic
{
	class SwitchStmt : AST
	{
		public AST m_pExpression;
		public Vector<AST> m_pExpressionVector;
		public Vector<AST> m_pStatementVector;
		public AST m_pDefaultStatement;
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
			Token pSwitchToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_SWITCH);
			if (pSwitchToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
				Console.Log("expected left paren");
				NumbatLogic.Assert.Plz(false);
				{
					return null;
				}
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
				Console.Log("expected expression");
				NumbatLogic.Assert.Plz(false);
				{
					return null;
				}
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) == null)
			{
				Console.Log("expected right paren");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				{
					return null;
				}
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
			{
				Console.Log("expected opening curly brace");
				NumbatLogic.Assert.Plz(false);
				{
					return null;
				}
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			SwitchStmt pSwitchStmt = new SwitchStmt();
			pSwitchStmt.m_pFirstToken = pSwitchToken;
			pSwitchStmt.m_pExpression = pExpression;
			{
				NumbatLogic.AST __1067118945 = pExpression;
				pExpression = null;
				pSwitchStmt.AddChild(__1067118945);
			}
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
				if (pSwitchStmt.m_pDefaultStatement != null)
				{
					Console.Log("expected default to be last thing in switch statement");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					{
						return null;
					}
				}
				Token pCaseToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CASE);
				Token pDefaultToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DEFAULT);
				if (pCaseToken == null && pDefaultToken == null)
				{
					Console.Log("expected case or default");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					{
						return null;
					}
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				if (pDefaultToken != null)
				{
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON) == null)
					{
						Console.Log("expected colon A");
						Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
						NumbatLogic.Assert.Plz(false);
						{
							return null;
						}
					}
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					AST pDefaultStatement = AST.CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
					if (pDefaultStatement == null)
					{
						Console.Log("expected case statement");
						Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
						NumbatLogic.Assert.Plz(false);
						{
							return null;
						}
					}
					AST pScopedDefaultStatement = null;
					if (pDefaultStatement.m_eType == AST.Type.AST_SCOPE)
					{
						NumbatLogic.AST __4278855511 = pDefaultStatement;
						pDefaultStatement = null;
						pScopedDefaultStatement = __4278855511;
					}
					else
					{
						pScopedDefaultStatement = new Scope();
						{
							NumbatLogic.AST __4278855511 = pDefaultStatement;
							pDefaultStatement = null;
							pScopedDefaultStatement.AddChild(__4278855511);
						}
					}
					pSwitchStmt.m_pDefaultStatement = pScopedDefaultStatement;
					{
						NumbatLogic.AST __1253506085 = pScopedDefaultStatement;
						pScopedDefaultStatement = null;
						pSwitchStmt.AddChild(__1253506085);
					}
					{
						continue;
					}
				}
				AST pCaseExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pCaseExpression == null)
				{
					Console.Log("expected case expression");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					{
						return null;
					}
				}
				pSwitchStmt.m_pExpressionVector.PushBack(pCaseExpression);
				{
					NumbatLogic.AST __3025039859 = pCaseExpression;
					pCaseExpression = null;
					pSwitchStmt.AddChild(__3025039859);
				}
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON) == null)
				{
					Console.Log("expected colon B");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					{
						return null;
					}
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CASE) != null)
				{
					pSwitchStmt.m_pStatementVector.PushBack(null);
					{
						continue;
					}
				}
				AST pCaseStatement = AST.CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
				if (pCaseStatement == null)
				{
					Console.Log("expected case statement");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					{
						return null;
					}
				}
				AST pScopedCaseStatement = null;
				if (pCaseStatement.m_eType == AST.Type.AST_SCOPE)
				{
					NumbatLogic.AST __3618575045 = pCaseStatement;
					pCaseStatement = null;
					pScopedCaseStatement = __3618575045;
				}
				else
				{
					pScopedCaseStatement = new Scope();
					{
						NumbatLogic.AST __3618575045 = pCaseStatement;
						pCaseStatement = null;
						pScopedCaseStatement.AddChild(__3618575045);
					}
				}
				pSwitchStmt.m_pStatementVector.PushBack(pScopedCaseStatement);
				{
					NumbatLogic.AST __128648087 = pScopedCaseStatement;
					pScopedCaseStatement = null;
					pSwitchStmt.AddChild(__128648087);
				}
			}
			pOffsetDatum.Set(pTempOffset);
			{
				NumbatLogic.SwitchStmt __3496390470 = pSwitchStmt;
				pSwitchStmt = null;
				{
					return __3496390470;
				}
			}
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			Util.Pad(nDepth, sOut);
			sOut.Append("switch (");
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut.Append(")\n");
			Util.Pad(nDepth, sOut);
			sOut.Append("{\n");
			nDepth++;
			for (int i = 0; i < m_pExpressionVector.GetSize(); i++)
			{
				AST pCaseExpression = m_pExpressionVector.Get(i);
				AST pCaseStatement = m_pStatementVector.Get(i);
				Util.Pad(nDepth, sOut);
				sOut.Append("case ");
				pCaseExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
				sOut.Append(":\n");
				if (pCaseStatement != null)
				{
					pCaseStatement.Stringify(eLanguage, eOutputFile, nDepth, sOut);
					sOut.Append("\n");
				}
			}
			if (m_pDefaultStatement != null)
			{
				Util.Pad(nDepth, sOut);
				sOut.Append("default:\n");
				m_pDefaultStatement.Stringify(eLanguage, eOutputFile, nDepth, sOut);
				sOut.Append("\n");
			}
			nDepth--;
			Util.Pad(nDepth, sOut);
			sOut.AppendString("}\n");
		}

		~SwitchStmt()
		{
		}

	}
}

