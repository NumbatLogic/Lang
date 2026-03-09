#line 1 "../../../Source/Core/AST/RefExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/RefExpr.nll"
	class RefExpr : AST
	{
#line 6 "../../../Source/Core/AST/RefExpr.nll"
		public AST m_pExpression;
#line 8 "../../../Source/Core/AST/RefExpr.nll"
		public static RefExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pRefToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_REF);
#line 13 "../../../Source/Core/AST/RefExpr.nll"
			if (pRefToken == null)
			{
#line 14 "../../../Source/Core/AST/RefExpr.nll"
				return null;
			}
#line 15 "../../../Source/Core/AST/RefExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 18 "../../../Source/Core/AST/RefExpr.nll"
			if (pExpression == null)
			{
#line 20 "../../../Source/Core/AST/RefExpr.nll"
				Console.Log("expected expresssion");
#line 21 "../../../Source/Core/AST/RefExpr.nll"
				Assert.Plz(false);
#line 22 "../../../Source/Core/AST/RefExpr.nll"
				return null;
			}
			RefExpr pRefExpr = new RefExpr();
#line 27 "../../../Source/Core/AST/RefExpr.nll"
			pRefExpr.m_eType = AST.Type.AST_REF_EXPR;
#line 28 "../../../Source/Core/AST/RefExpr.nll"
			pRefExpr.m_pFirstToken = pRefToken;
#line 29 "../../../Source/Core/AST/RefExpr.nll"
			pRefExpr.m_pExpression = pExpression;
			NumbatLogic.AST __1929334319 = pExpression;
#line 30 "../../../Source/Core/AST/RefExpr.nll"
			pExpression = null;
#line 30 "../../../Source/Core/AST/RefExpr.nll"
			pRefExpr.AddChild(__1929334319);
#line 32 "../../../Source/Core/AST/RefExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.RefExpr __1130235351 = pRefExpr;
#line 33 "../../../Source/Core/AST/RefExpr.nll"
			pRefExpr = null;
#line 33 "../../../Source/Core/AST/RefExpr.nll"
			return __1130235351;
		}

#line 36 "../../../Source/Core/AST/RefExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 38 "../../../Source/Core/AST/RefExpr.nll"
			base.Validate(pValidator, pParent);
#line 42 "../../../Source/Core/AST/RefExpr.nll"
			if (m_pExpression.m_pValueType == null)
			{
				InternalString sTemp = new InternalString("ref expression has no value type");
#line 45 "../../../Source/Core/AST/RefExpr.nll"
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 46 "../../../Source/Core/AST/RefExpr.nll"
				return;
			}
#line 49 "../../../Source/Core/AST/RefExpr.nll"
			m_pValueType = m_pExpression.m_pValueType.Clone();
		}

#line 52 "../../../Source/Core/AST/RefExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 54 "../../../Source/Core/AST/RefExpr.nll"
			if (eLanguage == AST.Language.NLL || eLanguage == AST.Language.CS)
			{
#line 56 "../../../Source/Core/AST/RefExpr.nll"
				pOutputBuilder.m_sOut.Append("ref ");
			}
#line 58 "../../../Source/Core/AST/RefExpr.nll"
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

#line 4 "../../../Source/Core/AST/RefExpr.nll"
		public RefExpr()
		{
		}

	}
}

