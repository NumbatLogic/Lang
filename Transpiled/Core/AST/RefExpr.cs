#line 1 "../../../Source/Core/AST/RefExpr.nll"
namespace NumbatLogic
{
	class RefExpr : AST
	{
		public AST m_pExpression;
#line 7 "../../../Source/Core/AST/RefExpr.nll"
		public static RefExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 11 "../../../Source/Core/AST/RefExpr.nll"
			Token pRefToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_REF);
			if (pRefToken == null)
			{
#line 13 "../../../Source/Core/AST/RefExpr.nll"
				return null;
			}
#line 14 "../../../Source/Core/AST/RefExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 16 "../../../Source/Core/AST/RefExpr.nll"
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
				Console.Log("expected expresssion");
				Assert.Plz(false);
				return null;
			}
#line 24 "../../../Source/Core/AST/RefExpr.nll"
			RefExpr pRefExpr = new RefExpr();
#line 26 "../../../Source/Core/AST/RefExpr.nll"
			pRefExpr.m_eType = AST.Type.AST_REF_EXPR;
			pRefExpr.m_pFirstToken = pRefToken;
			pRefExpr.m_pExpression = pExpression;
			NumbatLogic.AST __1929334319 = pExpression;
#line 29 "../../../Source/Core/AST/RefExpr.nll"
			pExpression = null;
#line 29 "../../../Source/Core/AST/RefExpr.nll"
			pRefExpr.AddChild(__1929334319);
#line 31 "../../../Source/Core/AST/RefExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.RefExpr __1130235351 = pRefExpr;
#line 32 "../../../Source/Core/AST/RefExpr.nll"
			pRefExpr = null;
#line 32 "../../../Source/Core/AST/RefExpr.nll"
			return __1130235351;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
#line 41 "../../../Source/Core/AST/RefExpr.nll"
			if (m_pExpression.m_pValueType == null)
			{
				InternalString sTemp = new InternalString("ref expression has no value type");
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				return;
			}
#line 48 "../../../Source/Core/AST/RefExpr.nll"
			m_pValueType = m_pExpression.m_pValueType.Clone();
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			if (eLanguage == AST.Language.NLL || eLanguage == AST.Language.CS)
			{
				pOutputBuilder.m_sOut.Append("ref ");
			}
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

#line 3 "../../../Source/Core/AST/RefExpr.nll"
		public RefExpr()
		{
		}

	}
}

