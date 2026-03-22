#include "ArrayLookup.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"
#include "../OffsetDatum.hpp"
#include "Identifier.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"

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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
namespace NumbatLogic
{
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
	ArrayLookup::ArrayLookup()
	{
		m_pExpression = 0;
		m_pIndexExpressionVector = 0;
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		m_eType = AST::Type::AST_ARRAY_LOOKUP;
		m_pIndexExpressionVector = new Vector<AST*>();
	}

	ArrayLookup* ArrayLookup::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 21 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		AST* pExpression = Identifier::TryCreate(pTokenContainer, pTempOffset);
		if (pExpression == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
			return 0;
		}
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
			return 0;
		}
		ArrayLookup* pArrayLookup = new ArrayLookup();
		pArrayLookup->m_pFirstToken = pExpression->m_pFirstToken;
		pArrayLookup->m_pExpression = pExpression;
		NumbatLogic::AST* __1929399910 = pExpression;
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		pExpression = 0;
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		pArrayLookup->AddChild(__1929399910);
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		while (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT) != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
			AST* pIndexExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pIndexExpression == 0)
			{
				Console::Log("expected index expression");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pIndexExpression) delete pIndexExpression;
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pArrayLookup) delete pArrayLookup;
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
				return 0;
			}
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT) == 0)
			{
				Console::Log("expected right bracket");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pIndexExpression) delete pIndexExpression;
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pArrayLookup) delete pArrayLookup;
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
				return 0;
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 55 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
			pArrayLookup->m_pIndexExpressionVector->PushBack(pIndexExpression);
			NumbatLogic::AST* __2936435995 = pIndexExpression;
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
			pIndexExpression = 0;
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
			pArrayLookup->AddChild(__2936435995);
			if (pIndexExpression) delete pIndexExpression;
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ArrayLookup* __1205754173 = pArrayLookup;
#line 60 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		pArrayLookup = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 60 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		return __1205754173;
	}

	AST* ArrayLookup::BaseClone()
	{
		ArrayLookup* pArrayLookup = new ArrayLookup();
#line 67 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		AST* pExpression = m_pExpression->BaseClone();
		pArrayLookup->m_pExpression = pExpression;
		NumbatLogic::AST* __1929596715 = pExpression;
#line 69 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		pExpression = 0;
#line 69 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		pArrayLookup->AddChild(__1929596715);
#line 71 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		for (int i = 0; i < m_pIndexExpressionVector->GetSize(); i++)
		{
			AST* pIndexExpression = m_pIndexExpressionVector->Get(i)->BaseClone();
			pArrayLookup->m_pIndexExpressionVector->PushBack(pIndexExpression);
			NumbatLogic::AST* __2936567192 = pIndexExpression;
#line 75 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
			pIndexExpression = 0;
#line 75 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
			pArrayLookup->AddChild(__2936567192);
			if (pIndexExpression) delete pIndexExpression;
		}
		NumbatLogic::ArrayLookup* __1205819781 = pArrayLookup;
		pArrayLookup = 0;
		if (pExpression) delete pExpression;
#line 79 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		return __1205819781;
	}

	void ArrayLookup::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		if (m_pExpression->m_pValueType == 0)
		{
			pValidator->AddError("Unknown ValueType of m_pExpression", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			return;
		}
		m_pValueType = m_pExpression->m_pValueType->Clone();
	}

	void ArrayLookup::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		for (int i = 0; i < m_pIndexExpressionVector->GetSize(); i++)
		{
			pOutputBuilder->m_sOut->AppendChar('[');
			m_pIndexExpressionVector->Get(i)->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder->m_sOut->AppendChar(']');
		}
	}

#line 5 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
	ArrayLookup::~ArrayLookup()
	{
		if (m_pIndexExpressionVector) delete m_pIndexExpressionVector;
	}

}

