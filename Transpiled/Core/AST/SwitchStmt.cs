#line 1 "../../../Source/Core/AST/SwitchStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/SwitchStmt.nll"
	class SwitchStmt : AST
	{
#line 6 "../../../Source/Core/AST/SwitchStmt.nll"
		public AST m_pExpression;
#line 7 "../../../Source/Core/AST/SwitchStmt.nll"
		public Vector<AST> m_pExpressionVector;
#line 8 "../../../Source/Core/AST/SwitchStmt.nll"
		public Vector<AST> m_pStatementVector;
#line 9 "../../../Source/Core/AST/SwitchStmt.nll"
		public AST m_pDefaultStatement;
#line 11 "../../../Source/Core/AST/SwitchStmt.nll"
		public SwitchStmt()
		{
#line 13 "../../../Source/Core/AST/SwitchStmt.nll"
			m_eType = AST.Type.AST_SWITCH_STMT;
#line 14 "../../../Source/Core/AST/SwitchStmt.nll"
			m_bStatement = true;
#line 15 "../../../Source/Core/AST/SwitchStmt.nll"
			m_pExpressionVector = new Vector<AST>();
#line 16 "../../../Source/Core/AST/SwitchStmt.nll"
			m_pStatementVector = new Vector<AST>();
#line 17 "../../../Source/Core/AST/SwitchStmt.nll"
			m_pDefaultStatement = null;
		}

#line 20 "../../../Source/Core/AST/SwitchStmt.nll"
		public static SwitchStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pSwitchToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_SWITCH);
#line 25 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pSwitchToken == null)
			{
#line 26 "../../../Source/Core/AST/SwitchStmt.nll"
				return null;
			}
#line 27 "../../../Source/Core/AST/SwitchStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 29 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
#line 31 "../../../Source/Core/AST/SwitchStmt.nll"
				Console.Log("expected left paren");
#line 32 "../../../Source/Core/AST/SwitchStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 33 "../../../Source/Core/AST/SwitchStmt.nll"
				return null;
			}
#line 35 "../../../Source/Core/AST/SwitchStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 38 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pExpression == null)
			{
#line 40 "../../../Source/Core/AST/SwitchStmt.nll"
				Console.Log("expected expression");
#line 41 "../../../Source/Core/AST/SwitchStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 42 "../../../Source/Core/AST/SwitchStmt.nll"
				return null;
			}
#line 45 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) == null)
			{
#line 47 "../../../Source/Core/AST/SwitchStmt.nll"
				Console.Log("expected right paren");
#line 48 "../../../Source/Core/AST/SwitchStmt.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 49 "../../../Source/Core/AST/SwitchStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 50 "../../../Source/Core/AST/SwitchStmt.nll"
				return null;
			}
#line 52 "../../../Source/Core/AST/SwitchStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 54 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
			{
#line 56 "../../../Source/Core/AST/SwitchStmt.nll"
				Console.Log("expected opening curly brace");
#line 57 "../../../Source/Core/AST/SwitchStmt.nll"
				NumbatLogic.Assert.Plz(false);
#line 58 "../../../Source/Core/AST/SwitchStmt.nll"
				return null;
			}
#line 60 "../../../Source/Core/AST/SwitchStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			SwitchStmt pSwitchStmt = new SwitchStmt();
#line 64 "../../../Source/Core/AST/SwitchStmt.nll"
			pSwitchStmt.m_pFirstToken = pSwitchToken;
#line 65 "../../../Source/Core/AST/SwitchStmt.nll"
			pSwitchStmt.m_pExpression = pExpression;
			NumbatLogic.AST __1929596711 = pExpression;
#line 66 "../../../Source/Core/AST/SwitchStmt.nll"
			pExpression = null;
#line 66 "../../../Source/Core/AST/SwitchStmt.nll"
			pSwitchStmt.AddChild(__1929596711);
#line 68 "../../../Source/Core/AST/SwitchStmt.nll"
			while (true)
			{
#line 70 "../../../Source/Core/AST/SwitchStmt.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
#line 72 "../../../Source/Core/AST/SwitchStmt.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 73 "../../../Source/Core/AST/SwitchStmt.nll"
					break;
				}
#line 76 "../../../Source/Core/AST/SwitchStmt.nll"
				if (pSwitchStmt.m_pDefaultStatement != null)
				{
#line 78 "../../../Source/Core/AST/SwitchStmt.nll"
					Console.Log("expected default to be last thing in switch statement");
#line 79 "../../../Source/Core/AST/SwitchStmt.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 80 "../../../Source/Core/AST/SwitchStmt.nll"
					NumbatLogic.Assert.Plz(false);
#line 81 "../../../Source/Core/AST/SwitchStmt.nll"
					return null;
				}
				Token pCaseToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CASE);
				Token pDefaultToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DEFAULT);
#line 86 "../../../Source/Core/AST/SwitchStmt.nll"
				if (pCaseToken == null && pDefaultToken == null)
				{
#line 88 "../../../Source/Core/AST/SwitchStmt.nll"
					Console.Log("expected case or default");
#line 89 "../../../Source/Core/AST/SwitchStmt.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 90 "../../../Source/Core/AST/SwitchStmt.nll"
					NumbatLogic.Assert.Plz(false);
#line 91 "../../../Source/Core/AST/SwitchStmt.nll"
					return null;
				}
#line 93 "../../../Source/Core/AST/SwitchStmt.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 95 "../../../Source/Core/AST/SwitchStmt.nll"
				if (pDefaultToken != null)
				{
#line 97 "../../../Source/Core/AST/SwitchStmt.nll"
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON) == null)
					{
#line 99 "../../../Source/Core/AST/SwitchStmt.nll"
						Console.Log("expected colon A");
#line 100 "../../../Source/Core/AST/SwitchStmt.nll"
						Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 101 "../../../Source/Core/AST/SwitchStmt.nll"
						NumbatLogic.Assert.Plz(false);
#line 102 "../../../Source/Core/AST/SwitchStmt.nll"
						return null;
					}
#line 104 "../../../Source/Core/AST/SwitchStmt.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					AST pDefaultStatement = AST.CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
#line 107 "../../../Source/Core/AST/SwitchStmt.nll"
					if (pDefaultStatement == null)
					{
#line 109 "../../../Source/Core/AST/SwitchStmt.nll"
						Console.Log("expected case statement");
#line 110 "../../../Source/Core/AST/SwitchStmt.nll"
						Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 111 "../../../Source/Core/AST/SwitchStmt.nll"
						NumbatLogic.Assert.Plz(false);
#line 112 "../../../Source/Core/AST/SwitchStmt.nll"
						return null;
					}
					AST pScopedDefaultStatement = null;
#line 116 "../../../Source/Core/AST/SwitchStmt.nll"
					if (pDefaultStatement.m_eType == AST.Type.AST_SCOPE)
					{
						NumbatLogic.AST __2021738808 = pDefaultStatement;
#line 117 "../../../Source/Core/AST/SwitchStmt.nll"
						pDefaultStatement = null;
#line 117 "../../../Source/Core/AST/SwitchStmt.nll"
						pScopedDefaultStatement = __2021738808;
					}
					else
					{
#line 120 "../../../Source/Core/AST/SwitchStmt.nll"
						pScopedDefaultStatement = new Scope();
						NumbatLogic.AST __2021804401 = pDefaultStatement;
#line 121 "../../../Source/Core/AST/SwitchStmt.nll"
						pDefaultStatement = null;
#line 121 "../../../Source/Core/AST/SwitchStmt.nll"
						pScopedDefaultStatement.AddChild(__2021804401);
					}
#line 124 "../../../Source/Core/AST/SwitchStmt.nll"
					pSwitchStmt.m_pDefaultStatement = pScopedDefaultStatement;
					NumbatLogic.AST __4074538021 = pScopedDefaultStatement;
#line 125 "../../../Source/Core/AST/SwitchStmt.nll"
					pScopedDefaultStatement = null;
#line 125 "../../../Source/Core/AST/SwitchStmt.nll"
					pSwitchStmt.AddChild(__4074538021);
#line 126 "../../../Source/Core/AST/SwitchStmt.nll"
					continue;
				}
				AST pCaseExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 130 "../../../Source/Core/AST/SwitchStmt.nll"
				if (pCaseExpression == null)
				{
#line 132 "../../../Source/Core/AST/SwitchStmt.nll"
					Console.Log("expected case expression");
#line 133 "../../../Source/Core/AST/SwitchStmt.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 134 "../../../Source/Core/AST/SwitchStmt.nll"
					NumbatLogic.Assert.Plz(false);
#line 135 "../../../Source/Core/AST/SwitchStmt.nll"
					return null;
				}
#line 137 "../../../Source/Core/AST/SwitchStmt.nll"
				pSwitchStmt.m_pExpressionVector.PushBack(pCaseExpression);
				NumbatLogic.AST __155144765 = pCaseExpression;
#line 138 "../../../Source/Core/AST/SwitchStmt.nll"
				pCaseExpression = null;
#line 138 "../../../Source/Core/AST/SwitchStmt.nll"
				pSwitchStmt.AddChild(__155144765);
#line 141 "../../../Source/Core/AST/SwitchStmt.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON) == null)
				{
#line 143 "../../../Source/Core/AST/SwitchStmt.nll"
					Console.Log("expected colon B");
#line 144 "../../../Source/Core/AST/SwitchStmt.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 145 "../../../Source/Core/AST/SwitchStmt.nll"
					NumbatLogic.Assert.Plz(false);
#line 146 "../../../Source/Core/AST/SwitchStmt.nll"
					return null;
				}
#line 148 "../../../Source/Core/AST/SwitchStmt.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 150 "../../../Source/Core/AST/SwitchStmt.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CASE) != null)
				{
#line 152 "../../../Source/Core/AST/SwitchStmt.nll"
					pSwitchStmt.m_pStatementVector.PushBack(null);
#line 153 "../../../Source/Core/AST/SwitchStmt.nll"
					continue;
				}
				AST pCaseStatement = AST.CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
#line 157 "../../../Source/Core/AST/SwitchStmt.nll"
				if (pCaseStatement == null)
				{
#line 159 "../../../Source/Core/AST/SwitchStmt.nll"
					Console.Log("expected case statement");
#line 160 "../../../Source/Core/AST/SwitchStmt.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 161 "../../../Source/Core/AST/SwitchStmt.nll"
					NumbatLogic.Assert.Plz(false);
#line 162 "../../../Source/Core/AST/SwitchStmt.nll"
					return null;
				}
				AST pScopedCaseStatement = null;
#line 166 "../../../Source/Core/AST/SwitchStmt.nll"
				if (pCaseStatement.m_eType == AST.Type.AST_SCOPE)
				{
					NumbatLogic.AST __2964786434 = pCaseStatement;
#line 167 "../../../Source/Core/AST/SwitchStmt.nll"
					pCaseStatement = null;
#line 167 "../../../Source/Core/AST/SwitchStmt.nll"
					pScopedCaseStatement = __2964786434;
				}
				else
				{
#line 170 "../../../Source/Core/AST/SwitchStmt.nll"
					pScopedCaseStatement = new Scope();
					NumbatLogic.AST __2964852027 = pCaseStatement;
#line 171 "../../../Source/Core/AST/SwitchStmt.nll"
					pCaseStatement = null;
#line 171 "../../../Source/Core/AST/SwitchStmt.nll"
					pScopedCaseStatement.AddChild(__2964852027);
				}
#line 174 "../../../Source/Core/AST/SwitchStmt.nll"
				pSwitchStmt.m_pStatementVector.PushBack(pScopedCaseStatement);
				NumbatLogic.AST __1629474447 = pScopedCaseStatement;
#line 175 "../../../Source/Core/AST/SwitchStmt.nll"
				pScopedCaseStatement = null;
#line 175 "../../../Source/Core/AST/SwitchStmt.nll"
				pSwitchStmt.AddChild(__1629474447);
			}
#line 178 "../../../Source/Core/AST/SwitchStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.SwitchStmt __1732082662 = pSwitchStmt;
#line 179 "../../../Source/Core/AST/SwitchStmt.nll"
			pSwitchStmt = null;
#line 179 "../../../Source/Core/AST/SwitchStmt.nll"
			return __1732082662;
		}

#line 182 "../../../Source/Core/AST/SwitchStmt.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 184 "../../../Source/Core/AST/SwitchStmt.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 185 "../../../Source/Core/AST/SwitchStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 187 "../../../Source/Core/AST/SwitchStmt.nll"
			pOutputBuilder.m_sOut.Append("switch (");
#line 188 "../../../Source/Core/AST/SwitchStmt.nll"
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 189 "../../../Source/Core/AST/SwitchStmt.nll"
			pOutputBuilder.m_sOut.Append(")\n");
#line 190 "../../../Source/Core/AST/SwitchStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 191 "../../../Source/Core/AST/SwitchStmt.nll"
			pOutputBuilder.m_sOut.Append("{\n");
#line 192 "../../../Source/Core/AST/SwitchStmt.nll"
			nDepth++;
#line 193 "../../../Source/Core/AST/SwitchStmt.nll"
			for (int i = 0; i < m_pExpressionVector.GetSize(); i++)
			{
				AST pCaseExpression = m_pExpressionVector.Get(i);
				AST pCaseStatement = m_pStatementVector.Get(i);
#line 198 "../../../Source/Core/AST/SwitchStmt.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 199 "../../../Source/Core/AST/SwitchStmt.nll"
				pOutputBuilder.m_sOut.Append("case ");
#line 200 "../../../Source/Core/AST/SwitchStmt.nll"
				pCaseExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 201 "../../../Source/Core/AST/SwitchStmt.nll"
				pOutputBuilder.m_sOut.Append(":\n");
#line 202 "../../../Source/Core/AST/SwitchStmt.nll"
				if (pCaseStatement != null)
				{
#line 204 "../../../Source/Core/AST/SwitchStmt.nll"
					pCaseStatement.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 205 "../../../Source/Core/AST/SwitchStmt.nll"
					pOutputBuilder.m_sOut.Append("\n");
				}
			}
#line 209 "../../../Source/Core/AST/SwitchStmt.nll"
			if (m_pDefaultStatement != null)
			{
#line 211 "../../../Source/Core/AST/SwitchStmt.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 212 "../../../Source/Core/AST/SwitchStmt.nll"
				pOutputBuilder.m_sOut.Append("default:\n");
#line 213 "../../../Source/Core/AST/SwitchStmt.nll"
				m_pDefaultStatement.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 214 "../../../Source/Core/AST/SwitchStmt.nll"
				pOutputBuilder.m_sOut.Append("\n");
			}
#line 217 "../../../Source/Core/AST/SwitchStmt.nll"
			nDepth--;
#line 218 "../../../Source/Core/AST/SwitchStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 219 "../../../Source/Core/AST/SwitchStmt.nll"
			pOutputBuilder.m_sOut.AppendString("}\n");
		}

#line 4 "../../../Source/Core/AST/SwitchStmt.nll"
		~SwitchStmt()
		{
		}

	}
}

