#include "StaticArray.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../ValueType.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class StaticArray;
	class AST;
	class OffsetDatum;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Token;
	class StaticArray;
	class AST;
	class Console;
	class Assert;
	class ValueType;
	class InternalString;
}
namespace NumbatLogic
{
	StaticArray::StaticArray()
	{
		m_eType = AST::Type::AST_STATIC_ARRAY;
	}

	StaticArray* StaticArray::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pSquareBracketLeftToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT);
		if (pSquareBracketLeftToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		StaticArray* pStaticArray = new StaticArray();
		pStaticArray->m_pFirstToken = pSquareBracketLeftToken;
		while (true)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
			AST* pElement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pElement == 0)
			{
				Console::Log("expected element");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pElement) delete pElement;
				if (pTempOffset) delete pTempOffset;
				if (pStaticArray) delete pStaticArray;
				return 0;
			}
			NumbatLogic::AST* __158822199 = pElement;
			pElement = 0;
			pStaticArray->AddChild(__158822199);
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT) != 0)
			{
				if (pElement) delete pElement;
				continue;
			}
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
			{
				Console::Log("expected comma");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			if (pElement) delete pElement;
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::StaticArray* __1466706106 = pStaticArray;
		pStaticArray = 0;
		if (pTempOffset) delete pTempOffset;
		return __1466706106;
	}

	void StaticArray::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::STATIC_ARRAY);
	}

	void StaticArray::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (eLanguage == AST::Language::CPP || eLanguage == AST::Language::CS)
			sOut->AppendChar('{');
		else
			sOut->AppendChar('[');
		AST* pParam = m_pFirstChild;
		while (pParam != 0)
		{
			if (pParam != m_pFirstChild)
				sOut->Append(", ");
			pParam->Stringify(eLanguage, eOutputFile, 0, sOut);
			pParam = pParam->m_pNextSibling;
		}
		if (eLanguage == AST::Language::CPP || eLanguage == AST::Language::CS)
			sOut->AppendChar('}');
		else
			sOut->AppendChar(']');
	}

}

