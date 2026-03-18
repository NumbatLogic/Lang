#line 1 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
namespace NumbatLogic
{
	class TrinaryExpr : AST
	{
		public AST m_pFirstExpression;
		public AST m_pSecondExpression;
		public AST m_pThirdExpression;
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		public TrinaryExpr()
		{
			m_eType = AST.Type.AST_DISOWN_EXP;
		}

		public static TrinaryExpr Create(AST pFirstExpressionTransition, TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			AST pFirstExpression = pFirstExpressionTransition;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			AST pSecondExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pSecondExpression == null)
			{
				Console.Log("expected second expresssion");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			Token pColonToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON);
			if (pColonToken == null)
			{
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
				return null;
			}
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 34 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			AST pThirdExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pThirdExpression == null)
			{
				Console.Log("expected second expresssion");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			TrinaryExpr pTrinaryExpr = new TrinaryExpr();
#line 45 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.m_pFirstExpression = pFirstExpression;
			pTrinaryExpr.m_pSecondExpression = pSecondExpression;
			pTrinaryExpr.m_pThirdExpression = pThirdExpression;
			NumbatLogic.AST __2029364893 = pFirstExpression;
			pFirstExpression = null;
#line 49 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.AddChild(__2029364893);
			NumbatLogic.AST __45120503 = pSecondExpression;
#line 50 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			pSecondExpression = null;
#line 50 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.AddChild(__45120503);
			NumbatLogic.AST __777254731 = pThirdExpression;
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			pThirdExpression = null;
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.AddChild(__777254731);
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.TrinaryExpr __2348216585 = pTrinaryExpr;
#line 54 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr = null;
#line 54 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			return __2348216585;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
#line 61 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			if (m_pSecondExpression.m_pValueType == null)
			{
				pValidator.AddError("Unknown ValueType of 2nd expression", m_pSecondExpression.m_pFirstToken.m_sFileName, m_pSecondExpression.m_pFirstToken.m_nLine, m_pSecondExpression.m_pFirstToken.m_nColumn);
				return;
			}
#line 67 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			if (m_pThirdExpression.m_pValueType == null)
			{
				pValidator.AddError("Unknown ValueType of 3rd expression", m_pThirdExpression.m_pFirstToken.m_sFileName, m_pThirdExpression.m_pFirstToken.m_nLine, m_pThirdExpression.m_pFirstToken.m_nColumn);
				return;
			}
#line 73 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			m_pValueType = m_pSecondExpression.m_pValueType.Clone();
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			m_pFirstExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder.m_sOut.Append(" ? ");
			m_pSecondExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder.m_sOut.Append(" : ");
			m_pThirdExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

	}
}

