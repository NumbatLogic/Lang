#line 1 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
namespace NumbatLogic
{
	class Paren : AST
	{
		public static Paren TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
			Token pOpeningToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT);
			if (pOpeningToken == null)
			{
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
				return null;
			}
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
			AST pChild = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pChild == null)
			{
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
				return null;
			}
			Token pClosingToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT);
			if (pClosingToken == null)
			{
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
				return null;
			}
#line 21 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
			Paren pParen = new Paren();
			pParen.m_eType = AST.Type.AST_PAREN;
			pParen.m_pFirstToken = pOpeningToken;
			NumbatLogic.AST __356832209 = pChild;
			pChild = null;
#line 27 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
			pParen.AddChild(__356832209);
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Paren __2093581495 = pParen;
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
			pParen = null;
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
			return __2093581495;
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

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.m_sOut.AppendChar('(');
			m_pFirstChild.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder.m_sOut.AppendChar(')');
		}

	}
}

