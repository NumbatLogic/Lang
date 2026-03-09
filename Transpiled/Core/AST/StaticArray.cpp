#include "StaticArray.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class StaticArray;
	class Console;
	class Assert;
	class ValueType;
	class OutputBuilder;
	class InternalString;
}
#line 1 "../../../Source/Core/AST/StaticArray.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/StaticArray.nll"
#line 6 "../../../Source/Core/AST/StaticArray.nll"
	StaticArray::StaticArray()
	{
#line 8 "../../../Source/Core/AST/StaticArray.nll"
		m_eType = AST::Type::AST_STATIC_ARRAY;
	}

#line 11 "../../../Source/Core/AST/StaticArray.nll"
	StaticArray* StaticArray::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pSquareBracketLeftToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT);
#line 16 "../../../Source/Core/AST/StaticArray.nll"
		if (pSquareBracketLeftToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 17 "../../../Source/Core/AST/StaticArray.nll"
			return 0;
		}
#line 18 "../../../Source/Core/AST/StaticArray.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		StaticArray* pStaticArray = new StaticArray();
#line 21 "../../../Source/Core/AST/StaticArray.nll"
		pStaticArray->m_pFirstToken = pSquareBracketLeftToken;
#line 23 "../../../Source/Core/AST/StaticArray.nll"
		while (true)
		{
#line 25 "../../../Source/Core/AST/StaticArray.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT) != 0)
			{
#line 27 "../../../Source/Core/AST/StaticArray.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 28 "../../../Source/Core/AST/StaticArray.nll"
				break;
			}
			AST* pElement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 32 "../../../Source/Core/AST/StaticArray.nll"
			if (pElement == 0)
			{
#line 34 "../../../Source/Core/AST/StaticArray.nll"
				Console::Log("expected element");
#line 35 "../../../Source/Core/AST/StaticArray.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 36 "../../../Source/Core/AST/StaticArray.nll"
				NumbatLogic::Assert::Plz(false);
				if (pElement) delete pElement;
				if (pTempOffset) delete pTempOffset;
				if (pStaticArray) delete pStaticArray;
#line 37 "../../../Source/Core/AST/StaticArray.nll"
				return 0;
			}
			NumbatLogic::AST* __984805329 = pElement;
#line 39 "../../../Source/Core/AST/StaticArray.nll"
			pElement = 0;
#line 39 "../../../Source/Core/AST/StaticArray.nll"
			pStaticArray->AddChild(__984805329);
#line 41 "../../../Source/Core/AST/StaticArray.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT) != 0)
			{
				if (pElement) delete pElement;
#line 42 "../../../Source/Core/AST/StaticArray.nll"
				continue;
			}
#line 44 "../../../Source/Core/AST/StaticArray.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
			{
#line 46 "../../../Source/Core/AST/StaticArray.nll"
				Console::Log("expected comma");
#line 47 "../../../Source/Core/AST/StaticArray.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 48 "../../../Source/Core/AST/StaticArray.nll"
				NumbatLogic::Assert::Plz(false);
			}
#line 50 "../../../Source/Core/AST/StaticArray.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			if (pElement) delete pElement;
		}
#line 53 "../../../Source/Core/AST/StaticArray.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::StaticArray* __2518123513 = pStaticArray;
#line 54 "../../../Source/Core/AST/StaticArray.nll"
		pStaticArray = 0;
		if (pTempOffset) delete pTempOffset;
#line 54 "../../../Source/Core/AST/StaticArray.nll"
		return __2518123513;
	}

#line 57 "../../../Source/Core/AST/StaticArray.nll"
	void StaticArray::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 59 "../../../Source/Core/AST/StaticArray.nll"
		AST::Validate(pValidator, pParent);
#line 60 "../../../Source/Core/AST/StaticArray.nll"
		m_pValueType = new ValueType(ValueType::Type::STATIC_ARRAY);
	}

#line 63 "../../../Source/Core/AST/StaticArray.nll"
	void StaticArray::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 65 "../../../Source/Core/AST/StaticArray.nll"
		if (eLanguage == AST::Language::CPP || eLanguage == AST::Language::CS)
#line 66 "../../../Source/Core/AST/StaticArray.nll"
			pOutputBuilder->m_sOut->AppendChar('{');
		else
#line 68 "../../../Source/Core/AST/StaticArray.nll"
			pOutputBuilder->m_sOut->AppendChar('[');
		AST* pParam = m_pFirstChild;
#line 70 "../../../Source/Core/AST/StaticArray.nll"
		while (pParam != 0)
		{
#line 72 "../../../Source/Core/AST/StaticArray.nll"
			if (pParam != m_pFirstChild)
#line 73 "../../../Source/Core/AST/StaticArray.nll"
				pOutputBuilder->m_sOut->Append(", ");
#line 74 "../../../Source/Core/AST/StaticArray.nll"
			pParam->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 75 "../../../Source/Core/AST/StaticArray.nll"
			pParam = pParam->m_pNextSibling;
		}
#line 77 "../../../Source/Core/AST/StaticArray.nll"
		if (eLanguage == AST::Language::CPP || eLanguage == AST::Language::CS)
#line 78 "../../../Source/Core/AST/StaticArray.nll"
			pOutputBuilder->m_sOut->AppendChar('}');
		else
#line 80 "../../../Source/Core/AST/StaticArray.nll"
			pOutputBuilder->m_sOut->AppendChar(']');
	}

}

