namespace NumbatLogic
{
	class RefExpr : AST
	{
		public AST m_pExpression;
		public static RefExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pRefToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_REF);
			if (pRefToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
				Console.Log("expected expresssion");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			RefExpr pRefExpr = new RefExpr();
			pRefExpr.m_eType = AST.Type.AST_REF_EXPR;
			pRefExpr.m_pFirstToken = pRefToken;
			pRefExpr.m_pExpression = pExpression;
			NumbatLogic.AST __2491310498 = pExpression;
			pExpression = null;
			pRefExpr.AddChild(__2491310498);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.RefExpr __3051183261 = pRefExpr;
			pRefExpr = null;
			return __3051183261;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			m_pValueType = m_pExpression.m_pValueType.Clone();
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (eLanguage == AST.Language.NLL || eLanguage == AST.Language.CS)
			{
				sOut.Append("ref ");
			}
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
		}

		public RefExpr()
		{
		}

	}
}

