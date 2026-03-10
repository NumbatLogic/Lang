#line 1 "../../../Source/Core/AST/Paren.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/Paren.nll"
	class Paren : AST
	{
#line 5 "../../../Source/Core/AST/Paren.nll"
		public static Paren TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 7 "../../../Source/Core/AST/Paren.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 9 "../../../Source/Core/AST/Paren.nll"
			Token pOpeningToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT);
#line 10 "../../../Source/Core/AST/Paren.nll"
			if (pOpeningToken == null)
			{
#line 11 "../../../Source/Core/AST/Paren.nll"
				return null;
			}
#line 12 "../../../Source/Core/AST/Paren.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 14 "../../../Source/Core/AST/Paren.nll"
			AST pChild = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 15 "../../../Source/Core/AST/Paren.nll"
			if (pChild == null)
			{
#line 16 "../../../Source/Core/AST/Paren.nll"
				return null;
			}
#line 18 "../../../Source/Core/AST/Paren.nll"
			Token pClosingToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT);
#line 19 "../../../Source/Core/AST/Paren.nll"
			if (pClosingToken == null)
			{
#line 20 "../../../Source/Core/AST/Paren.nll"
				return null;
			}
#line 21 "../../../Source/Core/AST/Paren.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 23 "../../../Source/Core/AST/Paren.nll"
			Paren pParen = new Paren();
#line 24 "../../../Source/Core/AST/Paren.nll"
			pParen.m_eType = AST.Type.AST_PAREN;
#line 25 "../../../Source/Core/AST/Paren.nll"
			pParen.m_pFirstToken = pOpeningToken;
			NumbatLogic.AST __356832209 = pChild;
#line 27 "../../../Source/Core/AST/Paren.nll"
			pChild = null;
#line 27 "../../../Source/Core/AST/Paren.nll"
			pParen.AddChild(__356832209);
#line 29 "../../../Source/Core/AST/Paren.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Paren __2093581495 = pParen;
#line 30 "../../../Source/Core/AST/Paren.nll"
			pParen = null;
#line 30 "../../../Source/Core/AST/Paren.nll"
			return __2093581495;
		}

#line 33 "../../../Source/Core/AST/Paren.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 35 "../../../Source/Core/AST/Paren.nll"
			base.Validate(pValidator, pParent);
#line 36 "../../../Source/Core/AST/Paren.nll"
			if (m_pFirstChild.m_pValueType == null)
			{
#line 38 "../../../Source/Core/AST/Paren.nll"
				pValidator.AddError("No valuetype???", m_pFirstChild.m_pFirstToken.m_sFileName, m_pFirstChild.m_pFirstToken.m_nLine, m_pFirstChild.m_pFirstToken.m_nColumn);
#line 39 "../../../Source/Core/AST/Paren.nll"
				return;
			}
#line 41 "../../../Source/Core/AST/Paren.nll"
			m_pValueType = m_pFirstChild.m_pValueType.Clone();
		}

#line 44 "../../../Source/Core/AST/Paren.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 46 "../../../Source/Core/AST/Paren.nll"
			pOutputBuilder.m_sOut.AppendChar('(');
#line 47 "../../../Source/Core/AST/Paren.nll"
			m_pFirstChild.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 48 "../../../Source/Core/AST/Paren.nll"
			pOutputBuilder.m_sOut.AppendChar(')');
		}

	}
}

