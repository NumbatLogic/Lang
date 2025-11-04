#include "RefExpr.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../ValueType.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Console;
	class Assert;
	class RefExpr;
	class ValueType;
	class InternalString;
}
namespace NumbatLogic
{
	RefExpr* RefExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pRefToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_REF);
		if (pRefToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pExpression == 0)
		{
			Console::Log("expected expresssion");
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
			return 0;
		}
		RefExpr* pRefExpr = new RefExpr();
		pRefExpr->m_eType = AST::Type::AST_REF_EXPR;
		pRefExpr->m_pFirstToken = pRefToken;
		pRefExpr->m_pExpression = pExpression;
		NumbatLogic::AST* __2491310498 = pExpression;
		pExpression = 0;
		pRefExpr->AddChild(__2491310498);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::RefExpr* __3051183261 = pRefExpr;
		pRefExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
		return __3051183261;
	}

	void RefExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		m_pValueType = m_pExpression->m_pValueType->Clone();
	}

	void RefExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (eLanguage == AST::Language::NLL || eLanguage == AST::Language::CS)
		{
			sOut->Append("ref ");
		}
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
	}

	RefExpr::RefExpr()
	{
		m_pExpression = 0;
	}

}

