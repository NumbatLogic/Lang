#include "Paren.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class AST;
	class Paren;
	class Validator;
	class ValueType;
	class InternalString;
}
namespace NumbatLogic
{
	Paren* Paren::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pOpeningToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT);
		if (pOpeningToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pChild = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pChild == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pChild) delete pChild;
			return 0;
		}
		Token* pClosingToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT);
		if (pClosingToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pChild) delete pChild;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		Paren* pParen = new Paren();
		pParen->m_eType = AST::Type::AST_PAREN;
		pParen->m_pFirstToken = pOpeningToken;
		NumbatLogic::AST* __3863392504 = pChild;
		pChild = 0;
		pParen->AddChild(__3863392504);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::Paren* __987830577 = pParen;
		pParen = 0;
		if (pTempOffset) delete pTempOffset;
		if (pChild) delete pChild;
		return __987830577;
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

	void Paren::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		sOut->AppendChar('(');
		m_pFirstChild->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->AppendChar(')');
	}

}

