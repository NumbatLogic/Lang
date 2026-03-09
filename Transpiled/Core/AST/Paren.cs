#line 1 "../../../Source/Core/AST/Paren.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/Paren.nll"
	class Paren : AST
	{
#line 6 "../../../Source/Core/AST/Paren.nll"
		public static Paren TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pOpeningToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT);
#line 11 "../../../Source/Core/AST/Paren.nll"
			if (pOpeningToken == null)
			{
#line 12 "../../../Source/Core/AST/Paren.nll"
				return null;
			}
#line 13 "../../../Source/Core/AST/Paren.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pChild = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 16 "../../../Source/Core/AST/Paren.nll"
			if (pChild == null)
			{
#line 17 "../../../Source/Core/AST/Paren.nll"
				return null;
			}
			Token pClosingToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT);
#line 20 "../../../Source/Core/AST/Paren.nll"
			if (pClosingToken == null)
			{
#line 21 "../../../Source/Core/AST/Paren.nll"
				return null;
			}
#line 22 "../../../Source/Core/AST/Paren.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			Paren pParen = new Paren();
#line 25 "../../../Source/Core/AST/Paren.nll"
			pParen.m_eType = AST.Type.AST_PAREN;
#line 26 "../../../Source/Core/AST/Paren.nll"
			pParen.m_pFirstToken = pOpeningToken;
			NumbatLogic.AST __356832209 = pChild;
#line 28 "../../../Source/Core/AST/Paren.nll"
			pChild = null;
#line 28 "../../../Source/Core/AST/Paren.nll"
			pParen.AddChild(__356832209);
#line 30 "../../../Source/Core/AST/Paren.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Paren __2093581495 = pParen;
#line 31 "../../../Source/Core/AST/Paren.nll"
			pParen = null;
#line 31 "../../../Source/Core/AST/Paren.nll"
			return __2093581495;
		}

#line 34 "../../../Source/Core/AST/Paren.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 36 "../../../Source/Core/AST/Paren.nll"
			base.Validate(pValidator, pParent);
#line 37 "../../../Source/Core/AST/Paren.nll"
			if (m_pFirstChild.m_pValueType == null)
			{
#line 39 "../../../Source/Core/AST/Paren.nll"
				pValidator.AddError("No valuetype???", m_pFirstChild.m_pFirstToken.m_sFileName, m_pFirstChild.m_pFirstToken.m_nLine, m_pFirstChild.m_pFirstToken.m_nColumn);
#line 40 "../../../Source/Core/AST/Paren.nll"
				return;
			}
#line 42 "../../../Source/Core/AST/Paren.nll"
			m_pValueType = m_pFirstChild.m_pValueType.Clone();
		}

#line 45 "../../../Source/Core/AST/Paren.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 47 "../../../Source/Core/AST/Paren.nll"
			pOutputBuilder.m_sOut.AppendChar('(');
#line 48 "../../../Source/Core/AST/Paren.nll"
			m_pFirstChild.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 49 "../../../Source/Core/AST/Paren.nll"
			pOutputBuilder.m_sOut.AppendChar(')');
		}

	}
}

