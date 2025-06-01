namespace NumberDuck
{
	namespace Secret
	{
		class IfStmt : AST
		{
			public IfStmt()
			{
				m_bStatement = true;
			}

			public static IfStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
			{
				OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
				Token pIfToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_IF);
				if (pIfToken == null)
				{
					return null;
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
				{
					Console.Log("expected left paren");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					nbAssert.Assert(false);
					{
						return null;
					}
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				AST pCondition = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pCondition == null)
				{
					Console.Log("expected condition");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					nbAssert.Assert(false);
					{
						return null;
					}
				}
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
				AST pThen = AST.CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
				if (pThen == null)
				{
					Console.Log("expected statement");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					nbAssert.Assert(false);
					{
						return null;
					}
				}
				AST pElse = null;
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_ELSE) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					pElse = AST.CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
					if (pElse == null)
					{
						Console.Log("expected else statement");
						Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
						nbAssert.Assert(false);
						{
							return null;
						}
					}
				}
				IfStmt pIfStmt = new IfStmt();
				pIfStmt.m_eType = AST.Type.AST_IF_STMT;
				pIfStmt.m_pFirstToken = pIfToken;
				{
					NumberDuck.Secret.AST __3534699931 = pCondition;
					pCondition = null;
					pIfStmt.AddChild(__3534699931);
				}
				{
					NumberDuck.Secret.AST __1813633903 = pThen;
					pThen = null;
					pIfStmt.AddChild(__1813633903);
				}
				if (pElse != null)
				{
					NumberDuck.Secret.AST __1661904051 = pElse;
					pElse = null;
					pIfStmt.AddChild(__1661904051);
				}
				pOffsetDatum.Set(pTempOffset);
				{
					NumberDuck.Secret.IfStmt __2301836827 = pIfStmt;
					pIfStmt = null;
					{
						return __2301836827;
					}
				}
			}

			public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
			{
				AST pCondition = m_pFirstChild;
				AST pThen = pCondition.m_pNextSibling;
				AST pElse = pThen.m_pNextSibling;
				IfStmt pParentIfStmt = null;
				if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_IF_STMT)
					pParentIfStmt = (IfStmt)(m_pParent);
				if (pParentIfStmt != null && pParentIfStmt.m_pFirstChild.m_pNextSibling.m_pNextSibling == this)
					sOut.Append(" ");
				else
					Util.Pad(nDepth, sOut);
				sOut.Append("if (");
				pCondition.Stringify(eLanguage, eOutputFile, 0, sOut);
				sOut.Append(")\n");
				if (pThen.m_eType == AST.Type.AST_SCOPE)
					pThen.Stringify(eLanguage, eOutputFile, nDepth, sOut);
				else
					pThen.Stringify(eLanguage, eOutputFile, nDepth + 1, sOut);
				if (pElse != null)
				{
					Util.Pad(nDepth, sOut);
					if (pElse.m_eType == AST.Type.AST_IF_STMT)
					{
						sOut.Append("else");
						pElse.Stringify(eLanguage, eOutputFile, nDepth, sOut);
					}
					else
					{
						sOut.Append("else\n");
						if (pElse.m_eType == AST.Type.AST_SCOPE)
							pElse.Stringify(eLanguage, eOutputFile, nDepth, sOut);
						else
							pElse.Stringify(eLanguage, eOutputFile, nDepth + 1, sOut);
					}
				}
			}

		}
	}
}

