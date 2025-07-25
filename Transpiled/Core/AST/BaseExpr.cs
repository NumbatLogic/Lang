namespace NumbatLogic
{
	class BaseExpr : AST
	{
		public ClassDecl m_pBaseClassDecl;
		public static BaseExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pThisToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_BASE);
			if (pThisToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			BaseExpr pBaseExpr = new BaseExpr();
			pBaseExpr.m_eType = AST.Type.BASE_EXPR;
			pBaseExpr.m_pFirstToken = pThisToken;
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.BaseExpr __4218948322 = pBaseExpr;
			pBaseExpr = null;
			return __4218948322;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.CLASS_DECL_VALUE);
			AST pTestParent = m_pParent;
			while (true)
			{
				if (pTestParent == null)
				{
					pValidator.AddError("this is not the child of a ClassDec???", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
					return;
				}
				if (pTestParent.m_eType == AST.Type.AST_CLASS_DECL)
					break;
				pTestParent = pTestParent.m_pParent;
			}
			ClassDecl pClassDecl = (ClassDecl)(pTestParent);
			ClassDecl pBaseClassDecl = pClassDecl.GetBaseClassDecl();
			if (pBaseClassDecl == null)
			{
				pValidator.AddError("class does not have a base class!", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				return;
			}
			m_pValueType.m_pClassDecl = pClassDecl;
			m_pBaseClassDecl = pBaseClassDecl;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (eLanguage == AST.Language.CPP)
				m_pBaseClassDecl.m_pNameToken.Stringify(sOut);
			else
				sOut.Append("base");
		}

		public BaseExpr()
		{
		}

	}
}

