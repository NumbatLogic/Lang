namespace NumberDuck
{
	namespace Secret
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
					nbAssert.Assert(false);
					{
						return null;
					}
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
						nbAssert.Assert(false);
						{
							return null;
						}
					}
				}
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
				{
					Console.Log("expected semicolon");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					nbAssert.Assert(false);
					{
						return null;
					}
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				AST pConditionStatement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pConditionStatement == null)
				{
					Console.Log("expected condition statement");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					nbAssert.Assert(false);
					{
						return null;
					}
				}
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
				{
					Console.Log("expected semicolon");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					nbAssert.Assert(false);
					{
						return null;
					}
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				AST pLoopStatement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) == null)
				{
					Console.Log("expected right paren");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					nbAssert.Assert(false);
					{
						return null;
					}
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				AST pStatement = AST.CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
				if (pStatement == null)
				{
					Console.Log("expected statement");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					nbAssert.Assert(false);
				}
				ForStmt pForStmt = new ForStmt();
				pForStmt.m_pFirstToken = pForToken;
				{
					NumberDuck.Secret.AST __4132705276 = pBeforeStatement;
					pBeforeStatement = null;
					pForStmt.AddChild(__4132705276);
				}
				{
					NumberDuck.Secret.AST __658474541 = pConditionStatement;
					pConditionStatement = null;
					pForStmt.AddChild(__658474541);
				}
				if (pLoopStatement != null)
				{
					NumberDuck.Secret.AST __3980311021 = pLoopStatement;
					pLoopStatement = null;
					pForStmt.AddChild(__3980311021);
				}
				{
					NumberDuck.Secret.AST __688492598 = pStatement;
					pStatement = null;
					pForStmt.AddChild(__688492598);
				}
				pOffsetDatum.Set(pTempOffset);
				{
					NumberDuck.Secret.ForStmt __3863278161 = pForStmt;
					pForStmt = null;
					{
						return __3863278161;
					}
				}
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
				if (pStatement.m_eType == AST.Type.AST_SCOPE)
					pStatement.Stringify(eLanguage, eOutputFile, nDepth, sOut);
				else
					pStatement.Stringify(eLanguage, eOutputFile, nDepth + 1, sOut);
			}

		}
	}
}

