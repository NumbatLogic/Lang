namespace NumbatLogic
{
	class ArrayLookup : AST
	{
		public AST m_pExpression;
		public Vector<AST> m_pIndexExpressionVector;
		public ArrayLookup()
		{
			m_eType = AST.Type.AST_ARRAY_LOOKUP;
			m_pIndexExpressionVector = new Vector<AST>();
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
			ArrayLookup pArrayLookup = new ArrayLookup();
			pArrayLookup.m_pFirstToken = pExpression.m_pFirstToken;
			pArrayLookup.m_pExpression = pExpression;
			NumbatLogic.AST __3112061645 = pExpression;
			pExpression = null;
			pArrayLookup.AddChild(__3112061645);
			while (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT) != null)
			{
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
				pArrayLookup.m_pIndexExpressionVector.PushBack(pIndexExpression);
				NumbatLogic.AST __2295631376 = pIndexExpression;
				pIndexExpression = null;
				pArrayLookup.AddChild(__2295631376);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ArrayLookup __1367242953 = pArrayLookup;
			pArrayLookup = null;
			return __1367242953;
		}

		public override AST BaseClone()
		{
			ArrayLookup pArrayLookup = new ArrayLookup();
			AST pExpression = m_pExpression.BaseClone();
			pArrayLookup.m_pExpression = pExpression;
			NumbatLogic.AST __3229533437 = pExpression;
			pExpression = null;
			pArrayLookup.AddChild(__3229533437);
			for (int i = 0; i < m_pIndexExpressionVector.GetSize(); i++)
			{
				AST pIndexExpression = m_pIndexExpressionVector.Get(i).BaseClone();
				pArrayLookup.m_pIndexExpressionVector.PushBack(pIndexExpression);
				NumbatLogic.AST __3553942599 = pIndexExpression;
				pIndexExpression = null;
				pArrayLookup.AddChild(__3553942599);
			}
			NumbatLogic.ArrayLookup __3548271526 = pArrayLookup;
			pArrayLookup = null;
			return __3548271526;
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
			for (int i = 0; i < m_pIndexExpressionVector.GetSize(); i++)
			{
				sOut.AppendChar('[');
				m_pIndexExpressionVector.Get(i).Stringify(eLanguage, eOutputFile, 0, sOut);
				sOut.AppendChar(']');
			}
		}

		~ArrayLookup()
		{
		}

	}
}

