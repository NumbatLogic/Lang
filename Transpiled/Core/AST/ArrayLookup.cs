#line 1 "../../../Source/Core/AST/ArrayLookup.nll"
namespace NumbatLogic
{
#line 5 "../../../Source/Core/AST/ArrayLookup.nll"
	class ArrayLookup : AST
	{
#line 7 "../../../Source/Core/AST/ArrayLookup.nll"
		public AST m_pExpression;
#line 8 "../../../Source/Core/AST/ArrayLookup.nll"
		public Vector<AST> m_pIndexExpressionVector;
#line 10 "../../../Source/Core/AST/ArrayLookup.nll"
		public ArrayLookup()
		{
#line 12 "../../../Source/Core/AST/ArrayLookup.nll"
			m_eType = AST.Type.AST_ARRAY_LOOKUP;
#line 13 "../../../Source/Core/AST/ArrayLookup.nll"
			m_pIndexExpressionVector = new Vector<AST>();
		}

#line 16 "../../../Source/Core/AST/ArrayLookup.nll"
		public static ArrayLookup TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 18 "../../../Source/Core/AST/ArrayLookup.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 21 "../../../Source/Core/AST/ArrayLookup.nll"
			AST pExpression = Identifier.TryCreate(pTokenContainer, pTempOffset);
#line 22 "../../../Source/Core/AST/ArrayLookup.nll"
			if (pExpression == null)
			{
#line 23 "../../../Source/Core/AST/ArrayLookup.nll"
				return null;
			}
#line 25 "../../../Source/Core/AST/ArrayLookup.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT) == null)
			{
#line 26 "../../../Source/Core/AST/ArrayLookup.nll"
				return null;
			}
#line 28 "../../../Source/Core/AST/ArrayLookup.nll"
			ArrayLookup pArrayLookup = new ArrayLookup();
#line 29 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup.m_pFirstToken = pExpression.m_pFirstToken;
#line 30 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup.m_pExpression = pExpression;
			NumbatLogic.AST __1929399910 = pExpression;
#line 31 "../../../Source/Core/AST/ArrayLookup.nll"
			pExpression = null;
#line 31 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup.AddChild(__1929399910);
#line 33 "../../../Source/Core/AST/ArrayLookup.nll"
			while (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT) != null)
			{
#line 35 "../../../Source/Core/AST/ArrayLookup.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 37 "../../../Source/Core/AST/ArrayLookup.nll"
				AST pIndexExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 38 "../../../Source/Core/AST/ArrayLookup.nll"
				if (pIndexExpression == null)
				{
#line 40 "../../../Source/Core/AST/ArrayLookup.nll"
					Console.Log("expected index expression");
#line 41 "../../../Source/Core/AST/ArrayLookup.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 42 "../../../Source/Core/AST/ArrayLookup.nll"
					NumbatLogic.Assert.Plz(false);
#line 43 "../../../Source/Core/AST/ArrayLookup.nll"
					return null;
				}
#line 46 "../../../Source/Core/AST/ArrayLookup.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_RIGHT) == null)
				{
#line 48 "../../../Source/Core/AST/ArrayLookup.nll"
					Console.Log("expected right bracket");
#line 49 "../../../Source/Core/AST/ArrayLookup.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 50 "../../../Source/Core/AST/ArrayLookup.nll"
					NumbatLogic.Assert.Plz(false);
#line 51 "../../../Source/Core/AST/ArrayLookup.nll"
					return null;
				}
#line 53 "../../../Source/Core/AST/ArrayLookup.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 55 "../../../Source/Core/AST/ArrayLookup.nll"
				pArrayLookup.m_pIndexExpressionVector.PushBack(pIndexExpression);
				NumbatLogic.AST __2936435995 = pIndexExpression;
#line 56 "../../../Source/Core/AST/ArrayLookup.nll"
				pIndexExpression = null;
#line 56 "../../../Source/Core/AST/ArrayLookup.nll"
				pArrayLookup.AddChild(__2936435995);
			}
#line 59 "../../../Source/Core/AST/ArrayLookup.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ArrayLookup __1205754173 = pArrayLookup;
#line 60 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup = null;
#line 60 "../../../Source/Core/AST/ArrayLookup.nll"
			return __1205754173;
		}

#line 63 "../../../Source/Core/AST/ArrayLookup.nll"
		public override AST BaseClone()
		{
#line 65 "../../../Source/Core/AST/ArrayLookup.nll"
			ArrayLookup pArrayLookup = new ArrayLookup();
#line 67 "../../../Source/Core/AST/ArrayLookup.nll"
			AST pExpression = m_pExpression.BaseClone();
#line 68 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup.m_pExpression = pExpression;
			NumbatLogic.AST __1929596715 = pExpression;
#line 69 "../../../Source/Core/AST/ArrayLookup.nll"
			pExpression = null;
#line 69 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup.AddChild(__1929596715);
#line 71 "../../../Source/Core/AST/ArrayLookup.nll"
			for (int i = 0; i < m_pIndexExpressionVector.GetSize(); i++)
			{
#line 73 "../../../Source/Core/AST/ArrayLookup.nll"
				AST pIndexExpression = m_pIndexExpressionVector.Get(i).BaseClone();
#line 74 "../../../Source/Core/AST/ArrayLookup.nll"
				pArrayLookup.m_pIndexExpressionVector.PushBack(pIndexExpression);
				NumbatLogic.AST __2936567192 = pIndexExpression;
#line 75 "../../../Source/Core/AST/ArrayLookup.nll"
				pIndexExpression = null;
#line 75 "../../../Source/Core/AST/ArrayLookup.nll"
				pArrayLookup.AddChild(__2936567192);
			}
			NumbatLogic.ArrayLookup __1205819781 = pArrayLookup;
#line 79 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup = null;
#line 79 "../../../Source/Core/AST/ArrayLookup.nll"
			return __1205819781;
		}

#line 82 "../../../Source/Core/AST/ArrayLookup.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 84 "../../../Source/Core/AST/ArrayLookup.nll"
			base.Validate(pValidator, pParent);
#line 85 "../../../Source/Core/AST/ArrayLookup.nll"
			if (m_pExpression.m_pValueType == null)
			{
#line 87 "../../../Source/Core/AST/ArrayLookup.nll"
				pValidator.AddError("Unknown ValueType of m_pExpression", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 88 "../../../Source/Core/AST/ArrayLookup.nll"
				return;
			}
#line 90 "../../../Source/Core/AST/ArrayLookup.nll"
			m_pValueType = m_pExpression.m_pValueType.Clone();
		}

#line 93 "../../../Source/Core/AST/ArrayLookup.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 95 "../../../Source/Core/AST/ArrayLookup.nll"
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 96 "../../../Source/Core/AST/ArrayLookup.nll"
			for (int i = 0; i < m_pIndexExpressionVector.GetSize(); i++)
			{
#line 98 "../../../Source/Core/AST/ArrayLookup.nll"
				pOutputBuilder.m_sOut.AppendChar('[');
#line 99 "../../../Source/Core/AST/ArrayLookup.nll"
				m_pIndexExpressionVector.Get(i).Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 100 "../../../Source/Core/AST/ArrayLookup.nll"
				pOutputBuilder.m_sOut.AppendChar(']');
			}
		}

#line 5 "../../../Source/Core/AST/ArrayLookup.nll"
		~ArrayLookup()
		{
		}

	}
}

