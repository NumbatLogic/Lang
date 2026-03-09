#line 1 "../../../Source/Core/AST/ArrayLookup.nll"
namespace NumbatLogic
{
#line 6 "../../../Source/Core/AST/ArrayLookup.nll"
	class ArrayLookup : AST
	{
#line 8 "../../../Source/Core/AST/ArrayLookup.nll"
		public AST m_pExpression;
#line 9 "../../../Source/Core/AST/ArrayLookup.nll"
		public Vector<AST> m_pIndexExpressionVector;
#line 11 "../../../Source/Core/AST/ArrayLookup.nll"
		public ArrayLookup()
		{
#line 13 "../../../Source/Core/AST/ArrayLookup.nll"
			m_eType = AST.Type.AST_ARRAY_LOOKUP;
#line 14 "../../../Source/Core/AST/ArrayLookup.nll"
			m_pIndexExpressionVector = new Vector<AST>();
		}

#line 17 "../../../Source/Core/AST/ArrayLookup.nll"
		public static ArrayLookup TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AST pExpression = Identifier.TryCreate(pTokenContainer, pTempOffset);
#line 23 "../../../Source/Core/AST/ArrayLookup.nll"
			if (pExpression == null)
			{
#line 24 "../../../Source/Core/AST/ArrayLookup.nll"
				return null;
			}
#line 26 "../../../Source/Core/AST/ArrayLookup.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT) == null)
			{
#line 27 "../../../Source/Core/AST/ArrayLookup.nll"
				return null;
			}
			ArrayLookup pArrayLookup = new ArrayLookup();
#line 30 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup.m_pFirstToken = pExpression.m_pFirstToken;
#line 31 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup.m_pExpression = pExpression;
			NumbatLogic.AST __1929399910 = pExpression;
#line 32 "../../../Source/Core/AST/ArrayLookup.nll"
			pExpression = null;
#line 32 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup.AddChild(__1929399910);
#line 34 "../../../Source/Core/AST/ArrayLookup.nll"
			while (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT) != null)
			{
#line 36 "../../../Source/Core/AST/ArrayLookup.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				AST pIndexExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 39 "../../../Source/Core/AST/ArrayLookup.nll"
				if (pIndexExpression == null)
				{
#line 41 "../../../Source/Core/AST/ArrayLookup.nll"
					Console.Log("expected index expression");
#line 42 "../../../Source/Core/AST/ArrayLookup.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 43 "../../../Source/Core/AST/ArrayLookup.nll"
					NumbatLogic.Assert.Plz(false);
#line 44 "../../../Source/Core/AST/ArrayLookup.nll"
					return null;
				}
#line 47 "../../../Source/Core/AST/ArrayLookup.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_RIGHT) == null)
				{
#line 49 "../../../Source/Core/AST/ArrayLookup.nll"
					Console.Log("expected right bracket");
#line 50 "../../../Source/Core/AST/ArrayLookup.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 51 "../../../Source/Core/AST/ArrayLookup.nll"
					NumbatLogic.Assert.Plz(false);
#line 52 "../../../Source/Core/AST/ArrayLookup.nll"
					return null;
				}
#line 54 "../../../Source/Core/AST/ArrayLookup.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 56 "../../../Source/Core/AST/ArrayLookup.nll"
				pArrayLookup.m_pIndexExpressionVector.PushBack(pIndexExpression);
				NumbatLogic.AST __2936435995 = pIndexExpression;
#line 57 "../../../Source/Core/AST/ArrayLookup.nll"
				pIndexExpression = null;
#line 57 "../../../Source/Core/AST/ArrayLookup.nll"
				pArrayLookup.AddChild(__2936435995);
			}
#line 60 "../../../Source/Core/AST/ArrayLookup.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ArrayLookup __1205754173 = pArrayLookup;
#line 61 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup = null;
#line 61 "../../../Source/Core/AST/ArrayLookup.nll"
			return __1205754173;
		}

#line 64 "../../../Source/Core/AST/ArrayLookup.nll"
		public override AST BaseClone()
		{
			ArrayLookup pArrayLookup = new ArrayLookup();
			AST pExpression = m_pExpression.BaseClone();
#line 69 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup.m_pExpression = pExpression;
			NumbatLogic.AST __1929596715 = pExpression;
#line 70 "../../../Source/Core/AST/ArrayLookup.nll"
			pExpression = null;
#line 70 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup.AddChild(__1929596715);
#line 72 "../../../Source/Core/AST/ArrayLookup.nll"
			for (int i = 0; i < m_pIndexExpressionVector.GetSize(); i++)
			{
				AST pIndexExpression = m_pIndexExpressionVector.Get(i).BaseClone();
#line 75 "../../../Source/Core/AST/ArrayLookup.nll"
				pArrayLookup.m_pIndexExpressionVector.PushBack(pIndexExpression);
				NumbatLogic.AST __2936567192 = pIndexExpression;
#line 76 "../../../Source/Core/AST/ArrayLookup.nll"
				pIndexExpression = null;
#line 76 "../../../Source/Core/AST/ArrayLookup.nll"
				pArrayLookup.AddChild(__2936567192);
			}
			NumbatLogic.ArrayLookup __1205819781 = pArrayLookup;
#line 80 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup = null;
#line 80 "../../../Source/Core/AST/ArrayLookup.nll"
			return __1205819781;
		}

#line 83 "../../../Source/Core/AST/ArrayLookup.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 85 "../../../Source/Core/AST/ArrayLookup.nll"
			base.Validate(pValidator, pParent);
#line 86 "../../../Source/Core/AST/ArrayLookup.nll"
			if (m_pExpression.m_pValueType == null)
			{
#line 88 "../../../Source/Core/AST/ArrayLookup.nll"
				pValidator.AddError("Unknown ValueType of m_pExpression", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 89 "../../../Source/Core/AST/ArrayLookup.nll"
				return;
			}
#line 91 "../../../Source/Core/AST/ArrayLookup.nll"
			m_pValueType = m_pExpression.m_pValueType.Clone();
		}

#line 94 "../../../Source/Core/AST/ArrayLookup.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 96 "../../../Source/Core/AST/ArrayLookup.nll"
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 97 "../../../Source/Core/AST/ArrayLookup.nll"
			for (int i = 0; i < m_pIndexExpressionVector.GetSize(); i++)
			{
#line 99 "../../../Source/Core/AST/ArrayLookup.nll"
				pOutputBuilder.m_sOut.AppendChar('[');
#line 100 "../../../Source/Core/AST/ArrayLookup.nll"
				m_pIndexExpressionVector.Get(i).Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 101 "../../../Source/Core/AST/ArrayLookup.nll"
				pOutputBuilder.m_sOut.AppendChar(']');
			}
		}

#line 6 "../../../Source/Core/AST/ArrayLookup.nll"
		~ArrayLookup()
		{
		}

	}
}

