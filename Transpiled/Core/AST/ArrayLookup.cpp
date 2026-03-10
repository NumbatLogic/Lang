#include "ArrayLookup.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../OffsetDatum.hpp"
#include "Identifier.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	template <class T>
	class Vector;
	class OffsetDatum;
	class Identifier;
	class TokenContainer;
	class Token;
	class ArrayLookup;
	class Console;
	class Assert;
	class Validator;
	class ValueType;
	class OutputBuilder;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/ArrayLookup.nll"
namespace NumbatLogic
{
#line 5 "../../../Source/Core/AST/ArrayLookup.nll"
#line 10 "../../../Source/Core/AST/ArrayLookup.nll"
	ArrayLookup::ArrayLookup()
	{
		m_pExpression = 0;
		m_pIndexExpressionVector = 0;
#line 12 "../../../Source/Core/AST/ArrayLookup.nll"
		m_eType = AST::Type::AST_ARRAY_LOOKUP;
#line 13 "../../../Source/Core/AST/ArrayLookup.nll"
		m_pIndexExpressionVector = new Vector<AST*>();
	}

#line 16 "../../../Source/Core/AST/ArrayLookup.nll"
	ArrayLookup* ArrayLookup::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AST* pExpression = Identifier::TryCreate(pTokenContainer, pTempOffset);
#line 22 "../../../Source/Core/AST/ArrayLookup.nll"
		if (pExpression == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 23 "../../../Source/Core/AST/ArrayLookup.nll"
			return 0;
		}
#line 25 "../../../Source/Core/AST/ArrayLookup.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 26 "../../../Source/Core/AST/ArrayLookup.nll"
			return 0;
		}
		ArrayLookup* pArrayLookup = new ArrayLookup();
#line 29 "../../../Source/Core/AST/ArrayLookup.nll"
		pArrayLookup->m_pFirstToken = pExpression->m_pFirstToken;
#line 30 "../../../Source/Core/AST/ArrayLookup.nll"
		pArrayLookup->m_pExpression = pExpression;
		NumbatLogic::AST* __1929399910 = pExpression;
#line 31 "../../../Source/Core/AST/ArrayLookup.nll"
		pExpression = 0;
#line 31 "../../../Source/Core/AST/ArrayLookup.nll"
		pArrayLookup->AddChild(__1929399910);
#line 33 "../../../Source/Core/AST/ArrayLookup.nll"
		while (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT) != 0)
		{
#line 35 "../../../Source/Core/AST/ArrayLookup.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			AST* pIndexExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 38 "../../../Source/Core/AST/ArrayLookup.nll"
			if (pIndexExpression == 0)
			{
#line 40 "../../../Source/Core/AST/ArrayLookup.nll"
				Console::Log("expected index expression");
#line 41 "../../../Source/Core/AST/ArrayLookup.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 42 "../../../Source/Core/AST/ArrayLookup.nll"
				NumbatLogic::Assert::Plz(false);
				if (pIndexExpression) delete pIndexExpression;
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pArrayLookup) delete pArrayLookup;
#line 43 "../../../Source/Core/AST/ArrayLookup.nll"
				return 0;
			}
#line 46 "../../../Source/Core/AST/ArrayLookup.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT) == 0)
			{
#line 48 "../../../Source/Core/AST/ArrayLookup.nll"
				Console::Log("expected right bracket");
#line 49 "../../../Source/Core/AST/ArrayLookup.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 50 "../../../Source/Core/AST/ArrayLookup.nll"
				NumbatLogic::Assert::Plz(false);
				if (pIndexExpression) delete pIndexExpression;
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pArrayLookup) delete pArrayLookup;
#line 51 "../../../Source/Core/AST/ArrayLookup.nll"
				return 0;
			}
#line 53 "../../../Source/Core/AST/ArrayLookup.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 55 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup->m_pIndexExpressionVector->PushBack(pIndexExpression);
			NumbatLogic::AST* __2936435995 = pIndexExpression;
#line 56 "../../../Source/Core/AST/ArrayLookup.nll"
			pIndexExpression = 0;
#line 56 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup->AddChild(__2936435995);
			if (pIndexExpression) delete pIndexExpression;
		}
#line 59 "../../../Source/Core/AST/ArrayLookup.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ArrayLookup* __1205754173 = pArrayLookup;
#line 60 "../../../Source/Core/AST/ArrayLookup.nll"
		pArrayLookup = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 60 "../../../Source/Core/AST/ArrayLookup.nll"
		return __1205754173;
	}

#line 63 "../../../Source/Core/AST/ArrayLookup.nll"
	AST* ArrayLookup::BaseClone()
	{
		ArrayLookup* pArrayLookup = new ArrayLookup();
		AST* pExpression = m_pExpression->BaseClone();
#line 68 "../../../Source/Core/AST/ArrayLookup.nll"
		pArrayLookup->m_pExpression = pExpression;
		NumbatLogic::AST* __1929596715 = pExpression;
#line 69 "../../../Source/Core/AST/ArrayLookup.nll"
		pExpression = 0;
#line 69 "../../../Source/Core/AST/ArrayLookup.nll"
		pArrayLookup->AddChild(__1929596715);
#line 71 "../../../Source/Core/AST/ArrayLookup.nll"
		for (int i = 0; i < m_pIndexExpressionVector->GetSize(); i++)
		{
			AST* pIndexExpression = m_pIndexExpressionVector->Get(i)->BaseClone();
#line 74 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup->m_pIndexExpressionVector->PushBack(pIndexExpression);
			NumbatLogic::AST* __2936567192 = pIndexExpression;
#line 75 "../../../Source/Core/AST/ArrayLookup.nll"
			pIndexExpression = 0;
#line 75 "../../../Source/Core/AST/ArrayLookup.nll"
			pArrayLookup->AddChild(__2936567192);
			if (pIndexExpression) delete pIndexExpression;
		}
		NumbatLogic::ArrayLookup* __1205819781 = pArrayLookup;
#line 79 "../../../Source/Core/AST/ArrayLookup.nll"
		pArrayLookup = 0;
		if (pExpression) delete pExpression;
#line 79 "../../../Source/Core/AST/ArrayLookup.nll"
		return __1205819781;
	}

#line 82 "../../../Source/Core/AST/ArrayLookup.nll"
	void ArrayLookup::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 84 "../../../Source/Core/AST/ArrayLookup.nll"
		AST::Validate(pValidator, pParent);
#line 85 "../../../Source/Core/AST/ArrayLookup.nll"
		if (m_pExpression->m_pValueType == 0)
		{
#line 87 "../../../Source/Core/AST/ArrayLookup.nll"
			pValidator->AddError("Unknown ValueType of m_pExpression", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 88 "../../../Source/Core/AST/ArrayLookup.nll"
			return;
		}
#line 90 "../../../Source/Core/AST/ArrayLookup.nll"
		m_pValueType = m_pExpression->m_pValueType->Clone();
	}

#line 93 "../../../Source/Core/AST/ArrayLookup.nll"
	void ArrayLookup::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 95 "../../../Source/Core/AST/ArrayLookup.nll"
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 96 "../../../Source/Core/AST/ArrayLookup.nll"
		for (int i = 0; i < m_pIndexExpressionVector->GetSize(); i++)
		{
#line 98 "../../../Source/Core/AST/ArrayLookup.nll"
			pOutputBuilder->m_sOut->AppendChar('[');
#line 99 "../../../Source/Core/AST/ArrayLookup.nll"
			m_pIndexExpressionVector->Get(i)->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 100 "../../../Source/Core/AST/ArrayLookup.nll"
			pOutputBuilder->m_sOut->AppendChar(']');
		}
	}

#line 5 "../../../Source/Core/AST/ArrayLookup.nll"
	ArrayLookup::~ArrayLookup()
	{
		if (m_pIndexExpressionVector) delete m_pIndexExpressionVector;
	}

}

