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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
	StaticArray::StaticArray()
	{
		m_eType = AST::Type::AST_STATIC_ARRAY;
	}

	StaticArray* StaticArray::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
		Token* pSquareBracketLeftToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT);
		if (pSquareBracketLeftToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
			return 0;
		}
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
		StaticArray* pStaticArray = new StaticArray();
		pStaticArray->m_pFirstToken = pSquareBracketLeftToken;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
		while (true)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
			AST* pElement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pElement == 0)
			{
				Console::Log("expected element");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pElement) delete pElement;
				if (pTempOffset) delete pTempOffset;
				if (pStaticArray) delete pStaticArray;
#line 36 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
				return 0;
			}
			NumbatLogic::AST* __984805329 = pElement;
#line 38 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
			pElement = 0;
#line 38 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
			pStaticArray->AddChild(__984805329);
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT) != 0)
			{
				if (pElement) delete pElement;
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
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
		NumbatLogic::StaticArray* __2518123513 = pStaticArray;
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
		pStaticArray = 0;
		if (pTempOffset) delete pTempOffset;
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
		return __2518123513;
	}

	void StaticArray::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		m_pValueType = new ValueType(ValueType::Type::STATIC_ARRAY);
	}

	void StaticArray::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (eLanguage == AST::Language::CPP || eLanguage == AST::Language::CS)
			pOutputBuilder->m_sOut->AppendChar('{');
		else
			pOutputBuilder->m_sOut->AppendChar('[');
		AST* pParam = m_pFirstChild;
		while (pParam != 0)
		{
			if (pParam != m_pFirstChild)
				pOutputBuilder->m_sOut->Append(", ");
			pParam->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pParam = pParam->m_pNextSibling;
		}
		if (eLanguage == AST::Language::CPP || eLanguage == AST::Language::CS)
			pOutputBuilder->m_sOut->AppendChar('}');
		else
			pOutputBuilder->m_sOut->AppendChar(']');
	}

}

