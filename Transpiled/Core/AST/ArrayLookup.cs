#line 1 "../../../Source/Core/AST/ArrayLookup.nll"
namespace NumbatLogic
{
#line 5 "../../../Source/Core/AST/ArrayLookup.nll"
	class ArrayLookup : AST
	{
		public AST m_pExpression;
		public Vector<AST> m_pIndexExpressionVector;
#line 10 "../../../Source/Core/AST/ArrayLookup.nll"
		public ArrayLookup()
		{
			m_eType = AST.Type.AST_ARRAY_LOOKUP;
			m_pIndexExpressionVector = new Vector<AST>();
		}

		public static ArrayLookup TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 21 "../../../Source/Core/AST/ArrayLookup.nll"
			AST pExpression = Identifier.TryCreate(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
#line 23 "../../../Source/Core/AST/ArrayLookup.nll"
				return null;
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT) == null)
			{
#line 26 "../../../Source/Core/AST/ArrayLookup.nll"
				return null;
			}
			ArrayLookup pArrayLookup = new ArrayLookup();
			pArrayLookup.m_pFirstToken = pExpression.m_pFirstToken;
			pArrayLookup.m_pExpression = pExpression;
			NumbatLogic.AST __1929399910 = pExpression;
#line 31 "../../../Source/Core/AST/ArrayLookup.nll"
			pExpression = null;
#line 31 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup.AddChild(__1929399910);
#line 33 "../../../Source/Core/AST/ArrayLookup.nll"
			while (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT) != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 37 "../../../Source/Core/AST/ArrayLookup.nll"
				AST pIndexExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pIndexExpression == null)
				{
					Console.Log("expected index expression");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
#line 46 "../../../Source/Core/AST/ArrayLookup.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_RIGHT) == null)
				{
					Console.Log("expected right bracket");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
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

		public override AST BaseClone()
		{
			ArrayLookup pArrayLookup = new ArrayLookup();
#line 67 "../../../Source/Core/AST/ArrayLookup.nll"
			AST pExpression = m_pExpression.BaseClone();
			pArrayLookup.m_pExpression = pExpression;
			NumbatLogic.AST __1929596715 = pExpression;
#line 69 "../../../Source/Core/AST/ArrayLookup.nll"
			pExpression = null;
#line 69 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup.AddChild(__1929596715);
#line 71 "../../../Source/Core/AST/ArrayLookup.nll"
			for (int i = 0; i < m_pIndexExpressionVector.GetSize(); i++)
			{
				AST pIndexExpression = m_pIndexExpressionVector.Get(i).BaseClone();
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

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			for (int i = 0; i < m_pIndexExpressionVector.GetSize(); i++)
			{
				pOutputBuilder.m_sOut.AppendChar('[');
				m_pIndexExpressionVector.Get(i).Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				pOutputBuilder.m_sOut.AppendChar(']');
			}
		}

#line 5 "../../../Source/Core/AST/ArrayLookup.nll"
		~ArrayLookup()
		{
		}

	}
}

