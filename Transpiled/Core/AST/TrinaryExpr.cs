#line 1 "../../../Source/Core/AST/TrinaryExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/TrinaryExpr.nll"
	class TrinaryExpr : AST
	{
#line 6 "../../../Source/Core/AST/TrinaryExpr.nll"
		public AST m_pFirstExpression;
#line 7 "../../../Source/Core/AST/TrinaryExpr.nll"
		public AST m_pSecondExpression;
#line 8 "../../../Source/Core/AST/TrinaryExpr.nll"
		public AST m_pThirdExpression;
#line 10 "../../../Source/Core/AST/TrinaryExpr.nll"
		public TrinaryExpr()
		{
#line 12 "../../../Source/Core/AST/TrinaryExpr.nll"
			m_eType = AST.Type.AST_DISOWN_EXP;
		}

#line 15 "../../../Source/Core/AST/TrinaryExpr.nll"
		public static TrinaryExpr Create(AST pFirstExpressionTransition, TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AST pFirstExpression = pFirstExpressionTransition;
			AST pSecondExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 22 "../../../Source/Core/AST/TrinaryExpr.nll"
			if (pSecondExpression == null)
			{
#line 24 "../../../Source/Core/AST/TrinaryExpr.nll"
				Console.Log("expected second expresssion");
#line 25 "../../../Source/Core/AST/TrinaryExpr.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 26 "../../../Source/Core/AST/TrinaryExpr.nll"
				NumbatLogic.Assert.Plz(false);
#line 27 "../../../Source/Core/AST/TrinaryExpr.nll"
				return null;
			}
			Token pColonToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON);
#line 31 "../../../Source/Core/AST/TrinaryExpr.nll"
			if (pColonToken == null)
			{
#line 32 "../../../Source/Core/AST/TrinaryExpr.nll"
				return null;
			}
#line 33 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pThirdExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 36 "../../../Source/Core/AST/TrinaryExpr.nll"
			if (pThirdExpression == null)
			{
#line 38 "../../../Source/Core/AST/TrinaryExpr.nll"
				Console.Log("expected second expresssion");
#line 39 "../../../Source/Core/AST/TrinaryExpr.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 40 "../../../Source/Core/AST/TrinaryExpr.nll"
				NumbatLogic.Assert.Plz(false);
#line 41 "../../../Source/Core/AST/TrinaryExpr.nll"
				return null;
			}
			TrinaryExpr pTrinaryExpr = new TrinaryExpr();
#line 46 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.m_pFirstExpression = pFirstExpression;
#line 47 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.m_pSecondExpression = pSecondExpression;
#line 48 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.m_pThirdExpression = pThirdExpression;
			NumbatLogic.AST __2029364893 = pFirstExpression;
#line 50 "../../../Source/Core/AST/TrinaryExpr.nll"
			pFirstExpression = null;
#line 50 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.AddChild(__2029364893);
			NumbatLogic.AST __45120503 = pSecondExpression;
#line 51 "../../../Source/Core/AST/TrinaryExpr.nll"
			pSecondExpression = null;
#line 51 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.AddChild(__45120503);
			NumbatLogic.AST __777254731 = pThirdExpression;
#line 52 "../../../Source/Core/AST/TrinaryExpr.nll"
			pThirdExpression = null;
#line 52 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr.AddChild(__777254731);
#line 54 "../../../Source/Core/AST/TrinaryExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.TrinaryExpr __2348216585 = pTrinaryExpr;
#line 55 "../../../Source/Core/AST/TrinaryExpr.nll"
			pTrinaryExpr = null;
#line 55 "../../../Source/Core/AST/TrinaryExpr.nll"
			return __2348216585;
		}

#line 58 "../../../Source/Core/AST/TrinaryExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 60 "../../../Source/Core/AST/TrinaryExpr.nll"
			base.Validate(pValidator, pParent);
#line 62 "../../../Source/Core/AST/TrinaryExpr.nll"
			if (m_pSecondExpression.m_pValueType == null)
			{
#line 64 "../../../Source/Core/AST/TrinaryExpr.nll"
				pValidator.AddError("Unknown ValueType of 2nd expression", m_pSecondExpression.m_pFirstToken.m_sFileName, m_pSecondExpression.m_pFirstToken.m_nLine, m_pSecondExpression.m_pFirstToken.m_nColumn);
#line 65 "../../../Source/Core/AST/TrinaryExpr.nll"
				return;
			}
#line 68 "../../../Source/Core/AST/TrinaryExpr.nll"
			if (m_pThirdExpression.m_pValueType == null)
			{
#line 70 "../../../Source/Core/AST/TrinaryExpr.nll"
				pValidator.AddError("Unknown ValueType of 3rd expression", m_pThirdExpression.m_pFirstToken.m_sFileName, m_pThirdExpression.m_pFirstToken.m_nLine, m_pThirdExpression.m_pFirstToken.m_nColumn);
#line 71 "../../../Source/Core/AST/TrinaryExpr.nll"
				return;
			}
#line 74 "../../../Source/Core/AST/TrinaryExpr.nll"
			m_pValueType = m_pSecondExpression.m_pValueType.Clone();
		}

#line 77 "../../../Source/Core/AST/TrinaryExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 79 "../../../Source/Core/AST/TrinaryExpr.nll"
			m_pFirstExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 80 "../../../Source/Core/AST/TrinaryExpr.nll"
			pOutputBuilder.m_sOut.Append(" ? ");
#line 81 "../../../Source/Core/AST/TrinaryExpr.nll"
			m_pSecondExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 82 "../../../Source/Core/AST/TrinaryExpr.nll"
			pOutputBuilder.m_sOut.Append(" : ");
#line 83 "../../../Source/Core/AST/TrinaryExpr.nll"
			m_pThirdExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

	}
}

