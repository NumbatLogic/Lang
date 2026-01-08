namespace NumbatLogic
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
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pCondition = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pCondition == null)
			{
				Console.Log("expected condition");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) == null)
			{
				Console.Log("expected right paren");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			Scope pThenScope = Scope.TryCreate(pTokenContainer, pTempOffset, true);
			if (pThenScope == null)
			{
				Console.Log("expected then statement / scope");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			Scope pElseScope = null;
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_ELSE) != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				pElseScope = Scope.TryCreate(pTokenContainer, pTempOffset, true);
				if (pElseScope == null)
				{
					Console.Log("expected else statement / scope");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
			}
			IfStmt pIfStmt = new IfStmt();
			pIfStmt.m_eType = AST.Type.AST_IF_STMT;
			pIfStmt.m_pFirstToken = pIfToken;
			NumbatLogic.AST __86400392 = pCondition;
			pCondition = null;
			pIfStmt.AddChild(__86400392);
			NumbatLogic.Scope __3484778949 = pThenScope;
			pThenScope = null;
			pIfStmt.AddChild(__3484778949);
			if (pElseScope != null)
			{
				NumbatLogic.Scope __1642439819 = pElseScope;
				pElseScope = null;
				pIfStmt.AddChild(__1642439819);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.IfStmt __816210157 = pIfStmt;
			pIfStmt = null;
			return __816210157;
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
			pThen.Stringify(eLanguage, eOutputFile, nDepth, sOut);
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
					pElse.Stringify(eLanguage, eOutputFile, nDepth, sOut);
				}
			}
		}

	}
}

