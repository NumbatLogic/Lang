#include "RefExpr.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Console;
	class Assert;
	class RefExpr;
	class InternalString;
	class Validator;
	class ValueType;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/RefExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/RefExpr.nll"
#line 7 "../../../Source/Core/AST/RefExpr.nll"
	RefExpr* RefExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pRefToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_REF);
#line 12 "../../../Source/Core/AST/RefExpr.nll"
		if (pRefToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 13 "../../../Source/Core/AST/RefExpr.nll"
			return 0;
		}
#line 14 "../../../Source/Core/AST/RefExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 17 "../../../Source/Core/AST/RefExpr.nll"
		if (pExpression == 0)
		{
#line 19 "../../../Source/Core/AST/RefExpr.nll"
			Console::Log("expected expresssion");
#line 20 "../../../Source/Core/AST/RefExpr.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 21 "../../../Source/Core/AST/RefExpr.nll"
			return 0;
		}
		RefExpr* pRefExpr = new RefExpr();
#line 26 "../../../Source/Core/AST/RefExpr.nll"
		pRefExpr->m_eType = AST::Type::AST_REF_EXPR;
#line 27 "../../../Source/Core/AST/RefExpr.nll"
		pRefExpr->m_pFirstToken = pRefToken;
#line 28 "../../../Source/Core/AST/RefExpr.nll"
		pRefExpr->m_pExpression = pExpression;
		NumbatLogic::AST* __1929334319 = pExpression;
#line 29 "../../../Source/Core/AST/RefExpr.nll"
		pExpression = 0;
#line 29 "../../../Source/Core/AST/RefExpr.nll"
		pRefExpr->AddChild(__1929334319);
#line 31 "../../../Source/Core/AST/RefExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::RefExpr* __1130235351 = pRefExpr;
#line 32 "../../../Source/Core/AST/RefExpr.nll"
		pRefExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 32 "../../../Source/Core/AST/RefExpr.nll"
		return __1130235351;
	}

#line 35 "../../../Source/Core/AST/RefExpr.nll"
	void RefExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 37 "../../../Source/Core/AST/RefExpr.nll"
		AST::Validate(pValidator, pParent);
#line 41 "../../../Source/Core/AST/RefExpr.nll"
		if (m_pExpression->m_pValueType == 0)
		{
			InternalString* sTemp = new InternalString("ref expression has no value type");
#line 44 "../../../Source/Core/AST/RefExpr.nll"
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
#line 45 "../../../Source/Core/AST/RefExpr.nll"
			return;
		}
#line 48 "../../../Source/Core/AST/RefExpr.nll"
		m_pValueType = m_pExpression->m_pValueType->Clone();
	}

#line 51 "../../../Source/Core/AST/RefExpr.nll"
	void RefExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 53 "../../../Source/Core/AST/RefExpr.nll"
		if (eLanguage == AST::Language::NLL || eLanguage == AST::Language::CS)
		{
#line 55 "../../../Source/Core/AST/RefExpr.nll"
			pOutputBuilder->m_sOut->Append("ref ");
		}
#line 57 "../../../Source/Core/AST/RefExpr.nll"
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

#line 3 "../../../Source/Core/AST/RefExpr.nll"
	RefExpr::RefExpr()
	{
		m_pExpression = 0;
	}

}

