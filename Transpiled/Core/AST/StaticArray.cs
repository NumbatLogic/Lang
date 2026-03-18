#line 1 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
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
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
			Token pSquareBracketLeftToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT);
			if (pSquareBracketLeftToken == null)
			{
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
				return null;
			}
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
			StaticArray pStaticArray = new StaticArray();
			pStaticArray.m_pFirstToken = pSquareBracketLeftToken;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
				AST pElement = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pElement == null)
				{
					Console.Log("expected element");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
				NumbatLogic.AST __984805329 = pElement;
#line 38 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
				pElement = null;
#line 38 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
				pStaticArray.AddChild(__984805329);
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_RIGHT) != null)
				{
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
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
#line 52 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.StaticArray __2518123513 = pStaticArray;
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
			pStaticArray = null;
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
			return __2518123513;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			m_pValueType = new ValueType(ValueType.Type.STATIC_ARRAY);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			if (eLanguage == AST.Language.CPP || eLanguage == AST.Language.CS)
				pOutputBuilder.m_sOut.AppendChar('{');
			else
				pOutputBuilder.m_sOut.AppendChar('[');
			AST pParam = m_pFirstChild;
			while (pParam != null)
			{
				if (pParam != m_pFirstChild)
					pOutputBuilder.m_sOut.Append(", ");
				pParam.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				pParam = pParam.m_pNextSibling;
			}
			if (eLanguage == AST.Language.CPP || eLanguage == AST.Language.CS)
				pOutputBuilder.m_sOut.AppendChar('}');
			else
				pOutputBuilder.m_sOut.AppendChar(']');
		}

	}
}

