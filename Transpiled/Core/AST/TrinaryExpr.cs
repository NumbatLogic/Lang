namespace NumbatLogic
{
	class TrinaryExpr : AST
	{
		public AST m_pFirstExpression;
		public AST m_pSecondExpression;
		public AST m_pThirdExpression;
		public TrinaryExpr()
		{
			m_eType = AST.Type.AST_DISOWN_EXP;
		}

		public static TrinaryExpr Create(AST pFirstExpressionTransition, TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AST pFirstExpression = pFirstExpressionTransition;
			AST pSecondExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pSecondExpression == null)
			{
				Console.Log("expected second expresssion");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			Token pColonToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON);
			if (pColonToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pThirdExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pThirdExpression == null)
			{
				Console.Log("expected second expresssion");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			TrinaryExpr pTrinaryExpr = new TrinaryExpr();
			pTrinaryExpr.m_pFirstExpression = pFirstExpression;
			pTrinaryExpr.m_pSecondExpression = pSecondExpression;
			pTrinaryExpr.m_pThirdExpression = pThirdExpression;
			NumbatLogic.AST __1176577974 = pFirstExpression;
			pFirstExpression = null;
			pTrinaryExpr.AddChild(__1176577974);
			NumbatLogic.AST __2317218345 = pSecondExpression;
			pSecondExpression = null;
			pTrinaryExpr.AddChild(__2317218345);
			NumbatLogic.AST __2588391620 = pThirdExpression;
			pThirdExpression = null;
			pTrinaryExpr.AddChild(__2588391620);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.TrinaryExpr __1659060397 = pTrinaryExpr;
			pTrinaryExpr = null;
			return __1659060397;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			if (m_pThirdExpression.m_pValueType == null)
			{
				pValidator.AddError("Unknown ValueType of 2nd expression", m_pSecondExpression.m_pFirstToken.m_sFileName, m_pSecondExpression.m_pFirstToken.m_nLine, m_pSecondExpression.m_pFirstToken.m_nColumn);
				return;
			}
			if (m_pThirdExpression.m_pValueType == null)
			{
				pValidator.AddError("Unknown ValueType of 3rd expression", m_pThirdExpression.m_pFirstToken.m_sFileName, m_pThirdExpression.m_pFirstToken.m_nLine, m_pThirdExpression.m_pFirstToken.m_nColumn);
				return;
			}
			m_pValueType = m_pSecondExpression.m_pValueType.Clone();
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			m_pFirstExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut.Append(" ? ");
			m_pSecondExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut.Append(" : ");
			m_pThirdExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
		}

	}
}

