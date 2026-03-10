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
#line 0 "../../../Source/Core/AST/StaticArray.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/StaticArray.nll"
#line 5 "../../../Source/Core/AST/StaticArray.nll"
	StaticArray::StaticArray()
	{
#line 7 "../../../Source/Core/AST/StaticArray.nll"
		m_eType = AST::Type::AST_STATIC_ARRAY;
	}

#line 10 "../../../Source/Core/AST/StaticArray.nll"
	StaticArray* StaticArray::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pSquareBracketLeftToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT);
#line 15 "../../../Source/Core/AST/StaticArray.nll"
		if (pSquareBracketLeftToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 16 "../../../Source/Core/AST/StaticArray.nll"
			return 0;
		}
#line 17 "../../../Source/Core/AST/StaticArray.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		StaticArray* pStaticArray = new StaticArray();
#line 20 "../../../Source/Core/AST/StaticArray.nll"
		pStaticArray->m_pFirstToken = pSquareBracketLeftToken;
#line 22 "../../../Source/Core/AST/StaticArray.nll"
		while (true)
		{
#line 24 "../../../Source/Core/AST/StaticArray.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT) != 0)
			{
#line 26 "../../../Source/Core/AST/StaticArray.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 27 "../../../Source/Core/AST/StaticArray.nll"
				break;
			}
			AST* pElement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 31 "../../../Source/Core/AST/StaticArray.nll"
			if (pElement == 0)
			{
#line 33 "../../../Source/Core/AST/StaticArray.nll"
				Console::Log("expected element");
#line 34 "../../../Source/Core/AST/StaticArray.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 35 "../../../Source/Core/AST/StaticArray.nll"
				NumbatLogic::Assert::Plz(false);
				if (pElement) delete pElement;
				if (pTempOffset) delete pTempOffset;
				if (pStaticArray) delete pStaticArray;
#line 36 "../../../Source/Core/AST/StaticArray.nll"
				return 0;
			}
			NumbatLogic::AST* __984805329 = pElement;
#line 38 "../../../Source/Core/AST/StaticArray.nll"
			pElement = 0;
#line 38 "../../../Source/Core/AST/StaticArray.nll"
			pStaticArray->AddChild(__984805329);
#line 40 "../../../Source/Core/AST/StaticArray.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT) != 0)
			{
				if (pElement) delete pElement;
#line 41 "../../../Source/Core/AST/StaticArray.nll"
				continue;
			}
#line 43 "../../../Source/Core/AST/StaticArray.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
			{
#line 45 "../../../Source/Core/AST/StaticArray.nll"
				Console::Log("expected comma");
#line 46 "../../../Source/Core/AST/StaticArray.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 47 "../../../Source/Core/AST/StaticArray.nll"
				NumbatLogic::Assert::Plz(false);
			}
#line 49 "../../../Source/Core/AST/StaticArray.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			if (pElement) delete pElement;
		}
#line 52 "../../../Source/Core/AST/StaticArray.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::StaticArray* __2518123513 = pStaticArray;
#line 53 "../../../Source/Core/AST/StaticArray.nll"
		pStaticArray = 0;
		if (pTempOffset) delete pTempOffset;
#line 53 "../../../Source/Core/AST/StaticArray.nll"
		return __2518123513;
	}

#line 56 "../../../Source/Core/AST/StaticArray.nll"
	void StaticArray::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 58 "../../../Source/Core/AST/StaticArray.nll"
		AST::Validate(pValidator, pParent);
#line 59 "../../../Source/Core/AST/StaticArray.nll"
		m_pValueType = new ValueType(ValueType::Type::STATIC_ARRAY);
	}

#line 62 "../../../Source/Core/AST/StaticArray.nll"
	void StaticArray::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 64 "../../../Source/Core/AST/StaticArray.nll"
		if (eLanguage == AST::Language::CPP || eLanguage == AST::Language::CS)
#line 65 "../../../Source/Core/AST/StaticArray.nll"
			pOutputBuilder->m_sOut->AppendChar('{');
		else
#line 67 "../../../Source/Core/AST/StaticArray.nll"
			pOutputBuilder->m_sOut->AppendChar('[');
		AST* pParam = m_pFirstChild;
#line 69 "../../../Source/Core/AST/StaticArray.nll"
		while (pParam != 0)
		{
#line 71 "../../../Source/Core/AST/StaticArray.nll"
			if (pParam != m_pFirstChild)
#line 72 "../../../Source/Core/AST/StaticArray.nll"
				pOutputBuilder->m_sOut->Append(", ");
#line 73 "../../../Source/Core/AST/StaticArray.nll"
			pParam->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 74 "../../../Source/Core/AST/StaticArray.nll"
			pParam = pParam->m_pNextSibling;
		}
#line 76 "../../../Source/Core/AST/StaticArray.nll"
		if (eLanguage == AST::Language::CPP || eLanguage == AST::Language::CS)
#line 77 "../../../Source/Core/AST/StaticArray.nll"
			pOutputBuilder->m_sOut->AppendChar('}');
		else
#line 79 "../../../Source/Core/AST/StaticArray.nll"
			pOutputBuilder->m_sOut->AppendChar(']');
	}

}

