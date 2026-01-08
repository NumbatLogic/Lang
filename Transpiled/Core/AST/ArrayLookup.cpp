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
	class InternalString;
}
namespace NumbatLogic
{
	ArrayLookup::ArrayLookup()
	{
		m_pExpression = 0;
		m_pIndexExpressionVector = 0;
		m_eType = AST::Type::AST_ARRAY_LOOKUP;
		m_pIndexExpressionVector = new Vector<AST*>();
	}

	ArrayLookup* ArrayLookup::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AST* pExpression = Identifier::TryCreate(pTokenContainer, pTempOffset);
		if (pExpression == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
			return 0;
		}
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
			return 0;
		}
		ArrayLookup* pArrayLookup = new ArrayLookup();
		pArrayLookup->m_pFirstToken = pExpression->m_pFirstToken;
		pArrayLookup->m_pExpression = pExpression;
		NumbatLogic::AST* __1929399910 = pExpression;
		pExpression = 0;
		pArrayLookup->AddChild(__1929399910);
		while (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT) != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
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
				return 0;
			}
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT) == 0)
			{
				Console::Log("expected right bracket");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pIndexExpression) delete pIndexExpression;
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pArrayLookup) delete pArrayLookup;
				return 0;
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			pArrayLookup->m_pIndexExpressionVector->PushBack(pIndexExpression);
			NumbatLogic::AST* __2936435995 = pIndexExpression;
			pIndexExpression = 0;
			pArrayLookup->AddChild(__2936435995);
			if (pIndexExpression) delete pIndexExpression;
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ArrayLookup* __1205754173 = pArrayLookup;
		pArrayLookup = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
		return __1205754173;
	}

	AST* ArrayLookup::BaseClone()
	{
		ArrayLookup* pArrayLookup = new ArrayLookup();
		AST* pExpression = m_pExpression->BaseClone();
		pArrayLookup->m_pExpression = pExpression;
		NumbatLogic::AST* __1929596715 = pExpression;
		pExpression = 0;
		pArrayLookup->AddChild(__1929596715);
		for (int i = 0; i < m_pIndexExpressionVector->GetSize(); i++)
		{
			AST* pIndexExpression = m_pIndexExpressionVector->Get(i)->BaseClone();
			pArrayLookup->m_pIndexExpressionVector->PushBack(pIndexExpression);
			NumbatLogic::AST* __2936567192 = pIndexExpression;
			pIndexExpression = 0;
			pArrayLookup->AddChild(__2936567192);
			if (pIndexExpression) delete pIndexExpression;
		}
		NumbatLogic::ArrayLookup* __1205819781 = pArrayLookup;
		pArrayLookup = 0;
		if (pExpression) delete pExpression;
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

	void ArrayLookup::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
		for (int i = 0; i < m_pIndexExpressionVector->GetSize(); i++)
		{
			sOut->AppendChar('[');
			m_pIndexExpressionVector->Get(i)->Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut->AppendChar(']');
		}
	}

	ArrayLookup::~ArrayLookup()
	{
		if (m_pIndexExpressionVector) delete m_pIndexExpressionVector;
	}

}

