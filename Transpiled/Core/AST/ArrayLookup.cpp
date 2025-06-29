#include "ArrayLookup.hpp"
#include "AST.hpp"
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
	class OffsetDatum;
	class AST;
	class ArrayLookup;
}
namespace NumbatLogic
{
	ArrayLookup::ArrayLookup()
	{
		m_pExpression = 0;
		m_pIndexExpression = 0;
		m_eType = AST::Type::AST_ARRAY_LOOKUP;
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
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pIndexExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pIndexExpression == 0)
		{
			Console::Log("expected index expression");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
			if (pIndexExpression) delete pIndexExpression;
			return 0;
		}
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT) == 0)
		{
			Console::Log("expected right bracket");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
			if (pIndexExpression) delete pIndexExpression;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ArrayLookup* pArrayLookup = new ArrayLookup();
		pArrayLookup->m_pFirstToken = pExpression->m_pFirstToken;
		pArrayLookup->m_pExpression = pExpression;
		pArrayLookup->m_pIndexExpression = pIndexExpression;
		NumbatLogic::AST* __1786680837 = pExpression;
		pExpression = 0;
		pArrayLookup->AddChild(__1786680837);
		NumbatLogic::AST* __1792315361 = pIndexExpression;
		pIndexExpression = 0;
		pArrayLookup->AddChild(__1792315361);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ArrayLookup* __1602094050 = pArrayLookup;
		pArrayLookup = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
		if (pIndexExpression) delete pIndexExpression;
		return __1602094050;
	}

	AST* ArrayLookup::BaseClone()
	{
		ArrayLookup* pArrayLookup = new ArrayLookup();
		AST* pExpression = m_pExpression->BaseClone();
		AST* pIndexExpression = m_pIndexExpression->BaseClone();
		pArrayLookup->m_pExpression = pExpression;
		pArrayLookup->m_pIndexExpression = pIndexExpression;
		NumbatLogic::AST* __75417520 = pExpression;
		pExpression = 0;
		pArrayLookup->AddChild(__75417520);
		NumbatLogic::AST* __2010445204 = pIndexExpression;
		pIndexExpression = 0;
		pArrayLookup->AddChild(__2010445204);
		NumbatLogic::ArrayLookup* __2256435930 = pArrayLookup;
		pArrayLookup = 0;
		if (pExpression) delete pExpression;
		if (pIndexExpression) delete pIndexExpression;
		return __2256435930;
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
		sOut->AppendChar('[');
		m_pIndexExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->AppendChar(']');
	}

}

