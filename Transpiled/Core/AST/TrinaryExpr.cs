#line 1 "../../../Source/Core/AST/TrinaryExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/TrinaryExpr.nll"
	class TrinaryExpr : AST
	{
#line 5 "../../../Source/Core/AST/TrinaryExpr.nll"
		public AST m_pFirstExpression;
#line 6 "../../../Source/Core/AST/TrinaryExpr.nll"
		public AST m_pSecondExpression;
#line 7 "../../../Source/Core/AST/TrinaryExpr.nll"
		public AST m_pThirdExpression;
#line 9 "../../../Source/Core/AST/TrinaryExpr.nll"
		public TrinaryExpr()
		{
#line 11 "../../../Source/Core/AST/TrinaryExpr.nll"
			m_eType = AST.Type.AST_DISOWN_EXP;
		}

#line 14 "../../../Source/Core/AST/TrinaryExpr.nll"
		public static TrinaryExpr Create(AST pFirstExpressionTransition, TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 16 "../../../Source/Core/AST/TrinaryExpr.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 18 "../../../Source/Core/AST/TrinaryExpr.nll"
			AST pFirstExpression = pFirstExpressionTransition;
#line 20 "../../../Source/Core/AST/TrinaryExpr.nll"
			AST pSecondExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 21 "../../../Source/Core/AST/TrinaryExpr.nll"
			if (pSecondExpression == null)
			{
#line 23 "../../../Source/Core/AST/TrinaryExpr.nll"
				Console.Log("expected second expresssion");
#line 24 "../../../Source/Core/AST/TrinaryExpr.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 25 "../../../Source/Core/AST/TrinaryExpr.nll"
				NumbatLogic.Assert.Plz(false);
#line 26 "../../../Source/Core/AST/TrinaryExpr.nll"
				return null;
			}
#line 29 "../../../Source/Core/AST/TrinaryExpr.nll"
			Token pColonToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON);
#line 30 "../../../Source/Core/AST/TrinaryExpr.nll"
			if (pColonToken == null)
			{
#line 31 "../../../Source/Core/AST/TrinaryExpr.nll"
				return null;
			}
#line 32 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 34 "../../../Source/Core/AST/TrinaryExpr.nll"
			AST pThirdExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 35 "../../../Source/Core/AST/TrinaryExpr.nll"
			if (pThirdExpression == null)
			{
#line 37 "../../../Source/Core/AST/TrinaryExpr.nll"
				Console.Log("expected second expresssion");
#line 38 "../../../Source/Core/AST/TrinaryExpr.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 39 "../../../Source/Core/AST/TrinaryExpr.nll"
				NumbatLogic.Assert.Plz(false);
#line 40 "../../../Source/Core/AST/TrinaryExpr.nll"
				return null;
			}
#line 43 "../../../Source/Core/AST/TrinaryExpr.nll"
			TrinaryExpr pTrinaryExpr = new TrinaryExpr();
#line 45 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.m_pFirstExpression = pFirstExpression;
#line 46 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.m_pSecondExpression = pSecondExpression;
#line 47 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.m_pThirdExpression = pThirdExpression;
			NumbatLogic.AST __2029364893 = pFirstExpression;
#line 49 "../../../Source/Core/AST/TrinaryExpr.nll"
			pFirstExpression = null;
#line 49 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.AddChild(__2029364893);
			NumbatLogic.AST __45120503 = pSecondExpression;
#line 50 "../../../Source/Core/AST/TrinaryExpr.nll"
			pSecondExpression = null;
#line 50 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.AddChild(__45120503);
			NumbatLogic.AST __777254731 = pThirdExpression;
#line 51 "../../../Source/Core/AST/TrinaryExpr.nll"
			pThirdExpression = null;
#line 51 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.AddChild(__777254731);
#line 53 "../../../Source/Core/AST/TrinaryExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.TrinaryExpr __2348216585 = pTrinaryExpr;
#line 54 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr = null;
#line 54 "../../../Source/Core/AST/TrinaryExpr.nll"
			return __2348216585;
		}

#line 57 "../../../Source/Core/AST/TrinaryExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 59 "../../../Source/Core/AST/TrinaryExpr.nll"
			base.Validate(pValidator, pParent);
#line 61 "../../../Source/Core/AST/TrinaryExpr.nll"
			if (m_pSecondExpression.m_pValueType == null)
			{
#line 63 "../../../Source/Core/AST/TrinaryExpr.nll"
				pValidator.AddError("Unknown ValueType of 2nd expression", m_pSecondExpression.m_pFirstToken.m_sFileName, m_pSecondExpression.m_pFirstToken.m_nLine, m_pSecondExpression.m_pFirstToken.m_nColumn);
#line 64 "../../../Source/Core/AST/TrinaryExpr.nll"
				return;
			}
#line 67 "../../../Source/Core/AST/TrinaryExpr.nll"
			if (m_pThirdExpression.m_pValueType == null)
			{
#line 69 "../../../Source/Core/AST/TrinaryExpr.nll"
				pValidator.AddError("Unknown ValueType of 3rd expression", m_pThirdExpression.m_pFirstToken.m_sFileName, m_pThirdExpression.m_pFirstToken.m_nLine, m_pThirdExpression.m_pFirstToken.m_nColumn);
#line 70 "../../../Source/Core/AST/TrinaryExpr.nll"
				return;
			}
#line 73 "../../../Source/Core/AST/TrinaryExpr.nll"
			m_pValueType = m_pSecondExpression.m_pValueType.Clone();
		}

#line 76 "../../../Source/Core/AST/TrinaryExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 78 "../../../Source/Core/AST/TrinaryExpr.nll"
			m_pFirstExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 79 "../../../Source/Core/AST/TrinaryExpr.nll"
			pOutputBuilder.m_sOut.Append(" ? ");
#line 80 "../../../Source/Core/AST/TrinaryExpr.nll"
			m_pSecondExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 81 "../../../Source/Core/AST/TrinaryExpr.nll"
			pOutputBuilder.m_sOut.Append(" : ");
#line 82 "../../../Source/Core/AST/TrinaryExpr.nll"
			m_pThirdExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

	}
}

