namespace NumbatLogic
{
	class StaticArray : AST
	{
		public StaticArray()
		{
			m_eType = AST.Type.AST_STATIC_ARRAY;
		}

		public static StaticArray TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pSquareBracketLeftToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT);
			if (pSquareBracketLeftToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			StaticArray pStaticArray = new StaticArray();
			pStaticArray.m_pFirstToken = pSquareBracketLeftToken;
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
				AST pElement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pElement == null)
				{
					Console.Log("expected element");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
				NumbatLogic.AST __1307930818 = pElement;
				pElement = null;
				pStaticArray.AddChild(__1307930818);
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_RIGHT) != null)
				{
					continue;
				}
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COMMA) == null)
				{
					Console.Log("expected comma");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.StaticArray __2560962993 = pStaticArray;
			pStaticArray = null;
			return __2560962993;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.STATIC_ARRAY);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (eLanguage == AST.Language.CPP || eLanguage == AST.Language.CS)
				sOut.AppendChar('{');
			else
				sOut.AppendChar('[');
			AST pParam = m_pFirstChild;
			while (pParam != null)
			{
				if (pParam != m_pFirstChild)
					sOut.Append(", ");
				pParam.Stringify(eLanguage, eOutputFile, 0, sOut);
				pParam = pParam.m_pNextSibling;
			}
			if (eLanguage == AST.Language.CPP || eLanguage == AST.Language.CS)
				sOut.AppendChar('}');
			else
				sOut.AppendChar(']');
		}

	}
}

