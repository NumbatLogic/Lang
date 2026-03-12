#line 1 "../../../Source/Core/AST/IfStmt.nll"
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
#line 14 "../../../Source/Core/AST/IfStmt.nll"
			Token pIfToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_IF);
			if (pIfToken == null)
			{
#line 16 "../../../Source/Core/AST/IfStmt.nll"
				return null;
			}
#line 17 "../../../Source/Core/AST/IfStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 19 "../../../Source/Core/AST/IfStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
				Console.Log("expected left paren");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 28 "../../../Source/Core/AST/IfStmt.nll"
			AST pCondition = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pCondition == null)
			{
				Console.Log("expected condition");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
#line 37 "../../../Source/Core/AST/IfStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) == null)
			{
				Console.Log("expected right paren");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 46 "../../../Source/Core/AST/IfStmt.nll"
			Scope pThenScope = Scope.TryCreate(pTokenContainer, pTempOffset, true);
			if (pThenScope == null)
			{
				Console.Log("expected then statement / scope");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
#line 55 "../../../Source/Core/AST/IfStmt.nll"
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
#line 69 "../../../Source/Core/AST/IfStmt.nll"
			IfStmt pIfStmt = new IfStmt();
#line 71 "../../../Source/Core/AST/IfStmt.nll"
			pIfStmt.m_eType = AST.Type.AST_IF_STMT;
			pIfStmt.m_pFirstToken = pIfToken;
			NumbatLogic.AST __86400392 = pCondition;
			pCondition = null;
#line 74 "../../../Source/Core/AST/IfStmt.nll"
			pIfStmt.AddChild(__86400392);
			NumbatLogic.Scope __3484778949 = pThenScope;
#line 75 "../../../Source/Core/AST/IfStmt.nll"
			pThenScope = null;
#line 75 "../../../Source/Core/AST/IfStmt.nll"
			pIfStmt.AddChild(__3484778949);
			if (pElseScope != null)
			{
				NumbatLogic.Scope __1642439819 = pElseScope;
#line 77 "../../../Source/Core/AST/IfStmt.nll"
				pElseScope = null;
#line 77 "../../../Source/Core/AST/IfStmt.nll"
				pIfStmt.AddChild(__1642439819);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.IfStmt __816210157 = pIfStmt;
#line 80 "../../../Source/Core/AST/IfStmt.nll"
			pIfStmt = null;
#line 80 "../../../Source/Core/AST/IfStmt.nll"
			return __816210157;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			AST pCondition = m_pFirstChild;
			AST pThen = pCondition.m_pNextSibling;
			AST pElse = pThen.m_pNextSibling;
#line 89 "../../../Source/Core/AST/IfStmt.nll"
			IfStmt pParentIfStmt = null;
			if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_IF_STMT)
				pParentIfStmt = (IfStmt)(m_pParent);
#line 93 "../../../Source/Core/AST/IfStmt.nll"
			if (pParentIfStmt != null && pParentIfStmt.m_pFirstChild.m_pNextSibling.m_pNextSibling == this)
				pOutputBuilder.m_sOut.Append(" ");
			else
			{
				pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
			}
#line 101 "../../../Source/Core/AST/IfStmt.nll"
			pOutputBuilder.m_sOut.Append("if (");
			pCondition.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder.m_sOut.Append(")\n");
			pThen.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			if (pElse != null)
			{
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
				if (pElse.m_eType == AST.Type.AST_IF_STMT)
				{
					pOutputBuilder.m_sOut.Append("else");
					pElse.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
				}
				else
				{
#line 116 "../../../Source/Core/AST/IfStmt.nll"
					pOutputBuilder.m_sOut.Append("else\n");
					pElse.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
				}
			}
		}

	}
}

