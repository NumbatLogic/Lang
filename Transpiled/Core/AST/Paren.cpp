#include "Paren.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Paren;
	class Validator;
	class ValueType;
	class OutputBuilder;
	class InternalString;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
	Paren* Paren::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
		Token* pOpeningToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT);
		if (pOpeningToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
			return 0;
		}
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
		AST* pChild = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pChild == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pChild) delete pChild;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
			return 0;
		}
		Token* pClosingToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT);
		if (pClosingToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pChild) delete pChild;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
			return 0;
		}
#line 21 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
		Paren* pParen = new Paren();
		pParen->m_eType = AST::Type::AST_PAREN;
		pParen->m_pFirstToken = pOpeningToken;
		NumbatLogic::AST* __356832209 = pChild;
		pChild = 0;
#line 27 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
		pParen->AddChild(__356832209);
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::Paren* __2093581495 = pParen;
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
		pParen = 0;
		if (pTempOffset) delete pTempOffset;
		if (pChild) delete pChild;
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
		return __2093581495;
	}

	void Paren::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		if (m_pFirstChild->m_pValueType == 0)
		{
			pValidator->AddError("No valuetype???", m_pFirstChild->m_pFirstToken->m_sFileName, m_pFirstChild->m_pFirstToken->m_nLine, m_pFirstChild->m_pFirstToken->m_nColumn);
			return;
		}
		m_pValueType = m_pFirstChild->m_pValueType->Clone();
	}

	void Paren::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->m_sOut->AppendChar('(');
		m_pFirstChild->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		pOutputBuilder->m_sOut->AppendChar(')');
	}

}

