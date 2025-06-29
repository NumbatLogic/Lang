namespace NumbatLogic
{
	class Paren : AST
	{
		public static Paren TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pOpeningToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT);
			if (pOpeningToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pChild = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pChild == null)
			{
				return null;
			}
			Token pClosingToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT);
			if (pClosingToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			Paren pParen = new Paren();
			pParen.m_eType = AST.Type.AST_PAREN;
			pParen.m_pFirstToken = pOpeningToken;
			NumbatLogic.AST __3863392504 = pChild;
			pChild = null;
			pParen.AddChild(__3863392504);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Paren __987830577 = pParen;
			pParen = null;
			return __987830577;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			if (m_pFirstChild.m_pValueType == null)
			{
				pValidator.AddError("No valuetype???", m_pFirstChild.m_pFirstToken.m_sFileName, m_pFirstChild.m_pFirstToken.m_nLine, m_pFirstChild.m_pFirstToken.m_nColumn);
				return;
			}
			m_pValueType = m_pFirstChild.m_pValueType.Clone();
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			sOut.AppendChar('(');
			m_pFirstChild.Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut.AppendChar(')');
		}

	}
}

