namespace NumberDuck
{
	namespace Secret
	{
		class ThisExpr : AST
		{
			public static ThisExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
			{
				OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
				Token pThisToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_THIS);
				if (pThisToken == null)
				{
					return null;
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				ThisExpr pThisExpr = new ThisExpr();
				pThisExpr.m_eType = AST.Type.THIS_EXPR;
				pThisExpr.m_pFirstToken = pThisToken;
				pOffsetDatum.Set(pTempOffset);
				{
					NumberDuck.Secret.ThisExpr __1019347393 = pThisExpr;
					pThisExpr = null;
					{
						return __1019347393;
					}
				}
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
				m_pValueType.m_pClassDecl = (ClassDecl)(pTestParent);
			}

			public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
			{
				sOut.Append("this");
			}

		}
	}
}

