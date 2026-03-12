#line 1 "../../../Source/Core/AST/OwnExpr.nll"
namespace NumbatLogic
{
	class OwnExpr : AST
	{
		public AST m_pExpression;
#line 7 "../../../Source/Core/AST/OwnExpr.nll"
		public static OwnExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 11 "../../../Source/Core/AST/OwnExpr.nll"
			Token pOwnToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_OWN);
			if (pOwnToken == null)
			{
#line 13 "../../../Source/Core/AST/OwnExpr.nll"
				return null;
			}
#line 14 "../../../Source/Core/AST/OwnExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 16 "../../../Source/Core/AST/OwnExpr.nll"
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
				Console.Log("expected expresssion");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
#line 24 "../../../Source/Core/AST/OwnExpr.nll"
			OwnExpr pOwnExpr = new OwnExpr();
#line 26 "../../../Source/Core/AST/OwnExpr.nll"
			pOwnExpr.m_eType = AST.Type.AST_OWN_EXP;
			pOwnExpr.m_pFirstToken = pOwnToken;
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

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
#line 39 "../../../Source/Core/AST/OwnExpr.nll"
			if (m_pExpression.m_pValueType == null)
			{
				pValidator.AddError("Unable to determine right side of own", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
#line 45 "../../../Source/Core/AST/OwnExpr.nll"
			if (m_pExpression.m_pValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE && m_pExpression.m_pValueType.m_eType != ValueType.Type.GENERIC_TYPE_DECL_VALUE)
			{
				InternalString sError = new InternalString("Expected right side of own to be a CLASS_DECL_VALUE or GENERIC_TYPE_DECL_VALUE, got: ");
				m_pExpression.m_pValueType.StringifyType(sError);
				pValidator.AddError(sError.GetExternalString(), m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
#line 53 "../../../Source/Core/AST/OwnExpr.nll"
			if (m_pExpression.m_pValueType.m_ePointerType != TypeRef.PointerType.TRANSITON)
			{
				pValidator.AddError("Expected right side of own to be a TRANSITON type", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
#line 59 "../../../Source/Core/AST/OwnExpr.nll"
			m_pValueType = m_pExpression.m_pValueType.Clone();
			m_pValueType.m_ePointerType = TypeRef.PointerType.OWNED_PREASSSIGN;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			if (eLanguage == AST.Language.NLL)
			{
				pOutputBuilder.m_sOut.Append("own ");
			}
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

#line 3 "../../../Source/Core/AST/OwnExpr.nll"
		public OwnExpr()
		{
		}

	}
}

