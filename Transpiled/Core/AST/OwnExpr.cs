namespace NumbatLogic
{
	class OwnExpr : AST
	{
		public AST m_pExpression;
		public static OwnExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pOwnToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_OWN);
			if (pOwnToken == null)
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
			OwnExpr pOwnExpr = new OwnExpr();
			pOwnExpr.m_eType = AST.Type.AST_OWN_EXP;
			pOwnExpr.m_pFirstToken = pOwnToken;
			pOwnExpr.m_pExpression = pExpression;
			NumbatLogic.AST __2637546178 = pExpression;
			pExpression = null;
			pOwnExpr.AddChild(__2637546178);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.OwnExpr __2951986774 = pOwnExpr;
			pOwnExpr = null;
			return __2951986774;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			if (m_pExpression.m_pValueType == null)
			{
				pValidator.AddError("Unable to determine right side of own", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
			if (m_pExpression.m_pValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE && m_pExpression.m_pValueType.m_eType != ValueType.Type.GENERIC_TYPE_DECL_VALUE)
			{
				InternalString sError = new InternalString("Expected right side of own to be a CLASS_DECL_VALUE or GENERIC_TYPE_DECL_VALUE, got: ");
				m_pExpression.m_pValueType.StringifyType(sError);
				pValidator.AddError(sError.GetExternalString(), m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
			if (m_pExpression.m_pValueType.m_ePointerType != TypeRef.PointerType.TRANSITON)
			{
				pValidator.AddError("Expected right side of own to be a TRANSITON type", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
			m_pValueType = m_pExpression.m_pValueType.Clone();
			m_pValueType.m_ePointerType = TypeRef.PointerType.OWNED_PREASSSIGN;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (eLanguage == AST.Language.NLL)
			{
				sOut.Append("own ");
			}
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
		}

		public OwnExpr()
		{
		}

	}
}

