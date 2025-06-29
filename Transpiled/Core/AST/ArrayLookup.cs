namespace NumbatLogic
{
	class ArrayLookup : AST
	{
		public AST m_pExpression;
		public AST m_pIndexExpression;
		public ArrayLookup()
		{
			m_eType = AST.Type.AST_ARRAY_LOOKUP;
		}

		public static ArrayLookup TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AST pExpression = Identifier.TryCreate(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
				return null;
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT) == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pIndexExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pIndexExpression == null)
			{
				Console.Log("expected index expression");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_RIGHT) == null)
			{
				Console.Log("expected right bracket");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			ArrayLookup pArrayLookup = new ArrayLookup();
			pArrayLookup.m_pFirstToken = pExpression.m_pFirstToken;
			pArrayLookup.m_pExpression = pExpression;
			pArrayLookup.m_pIndexExpression = pIndexExpression;
			NumbatLogic.AST __1786680837 = pExpression;
			pExpression = null;
			pArrayLookup.AddChild(__1786680837);
			NumbatLogic.AST __1792315361 = pIndexExpression;
			pIndexExpression = null;
			pArrayLookup.AddChild(__1792315361);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ArrayLookup __1602094050 = pArrayLookup;
			pArrayLookup = null;
			return __1602094050;
		}

		public override AST BaseClone()
		{
			ArrayLookup pArrayLookup = new ArrayLookup();
			AST pExpression = m_pExpression.BaseClone();
			AST pIndexExpression = m_pIndexExpression.BaseClone();
			pArrayLookup.m_pExpression = pExpression;
			pArrayLookup.m_pIndexExpression = pIndexExpression;
			NumbatLogic.AST __75417520 = pExpression;
			pExpression = null;
			pArrayLookup.AddChild(__75417520);
			NumbatLogic.AST __2010445204 = pIndexExpression;
			pIndexExpression = null;
			pArrayLookup.AddChild(__2010445204);
			NumbatLogic.ArrayLookup __2256435930 = pArrayLookup;
			pArrayLookup = null;
			return __2256435930;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			if (m_pExpression.m_pValueType == null)
			{
				pValidator.AddError("Unknown ValueType of m_pExpression", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				return;
			}
			m_pValueType = m_pExpression.m_pValueType.Clone();
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut.AppendChar('[');
			m_pIndexExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut.AppendChar(']');
		}

	}
}

