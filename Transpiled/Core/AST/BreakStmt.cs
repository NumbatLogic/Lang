namespace NumberDuck
{
	namespace Secret
	{
		class BreakStmt : AST
		{
			public BreakStmt()
			{
				m_bStatement = true;
			}

			public static BreakStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
			{
				OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
				Token pBreakToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_BREAK);
				if (pBreakToken == null)
				{
					return null;
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
				{
					Console.Log("expected semicolon");
					nbAssert.Assert(false);
					{
						return null;
					}
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				BreakStmt pBreakStmt = new BreakStmt();
				pBreakStmt.m_eType = AST.Type.AST_BREAK_STMT;
				pBreakStmt.m_pFirstToken = pBreakToken;
				pOffsetDatum.Set(pTempOffset);
				{
					NumberDuck.Secret.BreakStmt __4137675600 = pBreakStmt;
					pBreakStmt = null;
					{
						return __4137675600;
					}
				}
			}

			public override void Validate(Validator pValidator, OperatorExpr pParent)
			{
				base.Validate(pValidator, pParent);
				pValidator.InjectCleanup(this);
			}

			public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
			{
				Util.Pad(nDepth, sOut);
				sOut.Append("break;\n");
			}

		}
	}
}

