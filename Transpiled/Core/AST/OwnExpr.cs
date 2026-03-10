#line 1 "../../../Source/Core/AST/OwnExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/OwnExpr.nll"
	class OwnExpr : AST
	{
#line 5 "../../../Source/Core/AST/OwnExpr.nll"
		public AST m_pExpression;
#line 7 "../../../Source/Core/AST/OwnExpr.nll"
		public static OwnExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 9 "../../../Source/Core/AST/OwnExpr.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 11 "../../../Source/Core/AST/OwnExpr.nll"
			Token pOwnToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_OWN);
#line 12 "../../../Source/Core/AST/OwnExpr.nll"
			if (pOwnToken == null)
			{
#line 13 "../../../Source/Core/AST/OwnExpr.nll"
				return null;
			}
#line 14 "../../../Source/Core/AST/OwnExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 16 "../../../Source/Core/AST/OwnExpr.nll"
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 17 "../../../Source/Core/AST/OwnExpr.nll"
			if (pExpression == null)
			{
#line 19 "../../../Source/Core/AST/OwnExpr.nll"
				Console.Log("expected expresssion");
#line 20 "../../../Source/Core/AST/OwnExpr.nll"
				NumbatLogic.Assert.Plz(false);
#line 21 "../../../Source/Core/AST/OwnExpr.nll"
				return null;
			}
#line 24 "../../../Source/Core/AST/OwnExpr.nll"
			OwnExpr pOwnExpr = new OwnExpr();
#line 26 "../../../Source/Core/AST/OwnExpr.nll"
			pOwnExpr.m_eType = AST.Type.AST_OWN_EXP;
#line 27 "../../../Source/Core/AST/OwnExpr.nll"
			pOwnExpr.m_pFirstToken = pOwnToken;
#line 28 "../../../Source/Core/AST/OwnExpr.nll"
			pOwnExpr.m_pExpression = pExpression;
			NumbatLogic.AST __1929334319 = pExpression;
#line 29 "../../../Source/Core/AST/OwnExpr.nll"
			pExpression = null;
#line 29 "../../../Source/Core/AST/OwnExpr.nll"
			pOwnExpr.AddChild(__1929334319);
#line 31 "../../../Source/Core/AST/OwnExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.OwnExpr __4071014218 = pOwnExpr;
#line 32 "../../../Source/Core/AST/OwnExpr.nll"
			pOwnExpr = null;
#line 32 "../../../Source/Core/AST/OwnExpr.nll"
			return __4071014218;
		}

#line 35 "../../../Source/Core/AST/OwnExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 37 "../../../Source/Core/AST/OwnExpr.nll"
			base.Validate(pValidator, pParent);
#line 39 "../../../Source/Core/AST/OwnExpr.nll"
			if (m_pExpression.m_pValueType == null)
			{
#line 41 "../../../Source/Core/AST/OwnExpr.nll"
				pValidator.AddError("Unable to determine right side of own", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
#line 42 "../../../Source/Core/AST/OwnExpr.nll"
				return;
			}
#line 45 "../../../Source/Core/AST/OwnExpr.nll"
			if (m_pExpression.m_pValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE && m_pExpression.m_pValueType.m_eType != ValueType.Type.GENERIC_TYPE_DECL_VALUE)
			{
#line 47 "../../../Source/Core/AST/OwnExpr.nll"
				InternalString sError = new InternalString("Expected right side of own to be a CLASS_DECL_VALUE or GENERIC_TYPE_DECL_VALUE, got: ");
#line 48 "../../../Source/Core/AST/OwnExpr.nll"
				m_pExpression.m_pValueType.StringifyType(sError);
#line 49 "../../../Source/Core/AST/OwnExpr.nll"
				pValidator.AddError(sError.GetExternalString(), m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
#line 50 "../../../Source/Core/AST/OwnExpr.nll"
				return;
			}
#line 53 "../../../Source/Core/AST/OwnExpr.nll"
			if (m_pExpression.m_pValueType.m_ePointerType != TypeRef.PointerType.TRANSITON)
			{
#line 55 "../../../Source/Core/AST/OwnExpr.nll"
				pValidator.AddError("Expected right side of own to be a TRANSITON type", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
#line 56 "../../../Source/Core/AST/OwnExpr.nll"
				return;
			}
#line 59 "../../../Source/Core/AST/OwnExpr.nll"
			m_pValueType = m_pExpression.m_pValueType.Clone();
#line 60 "../../../Source/Core/AST/OwnExpr.nll"
			m_pValueType.m_ePointerType = TypeRef.PointerType.OWNED_PREASSSIGN;
		}

#line 63 "../../../Source/Core/AST/OwnExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 65 "../../../Source/Core/AST/OwnExpr.nll"
			if (eLanguage == AST.Language.NLL)
			{
#line 67 "../../../Source/Core/AST/OwnExpr.nll"
				pOutputBuilder.m_sOut.Append("own ");
			}
#line 69 "../../../Source/Core/AST/OwnExpr.nll"
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

#line 3 "../../../Source/Core/AST/OwnExpr.nll"
		public OwnExpr()
		{
		}

	}
}

