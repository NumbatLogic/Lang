#include "TrinaryExpr.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../TokenContainer.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Token.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Console;
	class TokenContainer;
	class Assert;
	class Token;
	class TrinaryExpr;
	class Validator;
	class ValueType;
	class OutputBuilder;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/TrinaryExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/TrinaryExpr.nll"
#line 9 "../../../Source/Core/AST/TrinaryExpr.nll"
	TrinaryExpr::TrinaryExpr()
	{
		m_pFirstExpression = 0;
		m_pSecondExpression = 0;
		m_pThirdExpression = 0;
#line 11 "../../../Source/Core/AST/TrinaryExpr.nll"
		m_eType = AST::Type::AST_DISOWN_EXP;
	}

#line 14 "../../../Source/Core/AST/TrinaryExpr.nll"
	TrinaryExpr* TrinaryExpr::Create(AST* pFirstExpressionTransition, TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AST* pFirstExpression = pFirstExpressionTransition;
		AST* pSecondExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 21 "../../../Source/Core/AST/TrinaryExpr.nll"
		if (pSecondExpression == 0)
		{
#line 23 "../../../Source/Core/AST/TrinaryExpr.nll"
			Console::Log("expected second expresssion");
#line 24 "../../../Source/Core/AST/TrinaryExpr.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 25 "../../../Source/Core/AST/TrinaryExpr.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pFirstExpression) delete pFirstExpression;
			if (pSecondExpression) delete pSecondExpression;
#line 26 "../../../Source/Core/AST/TrinaryExpr.nll"
			return 0;
		}
		Token* pColonToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COLON);
#line 30 "../../../Source/Core/AST/TrinaryExpr.nll"
		if (pColonToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pFirstExpression) delete pFirstExpression;
			if (pSecondExpression) delete pSecondExpression;
#line 31 "../../../Source/Core/AST/TrinaryExpr.nll"
			return 0;
		}
#line 32 "../../../Source/Core/AST/TrinaryExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pThirdExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 35 "../../../Source/Core/AST/TrinaryExpr.nll"
		if (pThirdExpression == 0)
		{
#line 37 "../../../Source/Core/AST/TrinaryExpr.nll"
			Console::Log("expected second expresssion");
#line 38 "../../../Source/Core/AST/TrinaryExpr.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 39 "../../../Source/Core/AST/TrinaryExpr.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pFirstExpression) delete pFirstExpression;
			if (pSecondExpression) delete pSecondExpression;
			if (pThirdExpression) delete pThirdExpression;
#line 40 "../../../Source/Core/AST/TrinaryExpr.nll"
			return 0;
		}
		TrinaryExpr* pTrinaryExpr = new TrinaryExpr();
#line 45 "../../../Source/Core/AST/TrinaryExpr.nll"
		pTrinaryExpr->m_pFirstExpression = pFirstExpression;
#line 46 "../../../Source/Core/AST/TrinaryExpr.nll"
		pTrinaryExpr->m_pSecondExpression = pSecondExpression;
#line 47 "../../../Source/Core/AST/TrinaryExpr.nll"
		pTrinaryExpr->m_pThirdExpression = pThirdExpression;
		NumbatLogic::AST* __2029364893 = pFirstExpression;
#line 49 "../../../Source/Core/AST/TrinaryExpr.nll"
		pFirstExpression = 0;
#line 49 "../../../Source/Core/AST/TrinaryExpr.nll"
		pTrinaryExpr->AddChild(__2029364893);
		NumbatLogic::AST* __45120503 = pSecondExpression;
#line 50 "../../../Source/Core/AST/TrinaryExpr.nll"
		pSecondExpression = 0;
#line 50 "../../../Source/Core/AST/TrinaryExpr.nll"
		pTrinaryExpr->AddChild(__45120503);
		NumbatLogic::AST* __777254731 = pThirdExpression;
#line 51 "../../../Source/Core/AST/TrinaryExpr.nll"
		pThirdExpression = 0;
#line 51 "../../../Source/Core/AST/TrinaryExpr.nll"
		pTrinaryExpr->AddChild(__777254731);
#line 53 "../../../Source/Core/AST/TrinaryExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::TrinaryExpr* __2348216585 = pTrinaryExpr;
#line 54 "../../../Source/Core/AST/TrinaryExpr.nll"
		pTrinaryExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pFirstExpression) delete pFirstExpression;
		if (pSecondExpression) delete pSecondExpression;
		if (pThirdExpression) delete pThirdExpression;
#line 54 "../../../Source/Core/AST/TrinaryExpr.nll"
		return __2348216585;
	}

#line 57 "../../../Source/Core/AST/TrinaryExpr.nll"
	void TrinaryExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 59 "../../../Source/Core/AST/TrinaryExpr.nll"
		AST::Validate(pValidator, pParent);
#line 61 "../../../Source/Core/AST/TrinaryExpr.nll"
		if (m_pSecondExpression->m_pValueType == 0)
		{
#line 63 "../../../Source/Core/AST/TrinaryExpr.nll"
			pValidator->AddError("Unknown ValueType of 2nd expression", m_pSecondExpression->m_pFirstToken->m_sFileName, m_pSecondExpression->m_pFirstToken->m_nLine, m_pSecondExpression->m_pFirstToken->m_nColumn);
#line 64 "../../../Source/Core/AST/TrinaryExpr.nll"
			return;
		}
#line 67 "../../../Source/Core/AST/TrinaryExpr.nll"
		if (m_pThirdExpression->m_pValueType == 0)
		{
#line 69 "../../../Source/Core/AST/TrinaryExpr.nll"
			pValidator->AddError("Unknown ValueType of 3rd expression", m_pThirdExpression->m_pFirstToken->m_sFileName, m_pThirdExpression->m_pFirstToken->m_nLine, m_pThirdExpression->m_pFirstToken->m_nColumn);
#line 70 "../../../Source/Core/AST/TrinaryExpr.nll"
			return;
		}
#line 73 "../../../Source/Core/AST/TrinaryExpr.nll"
		m_pValueType = m_pSecondExpression->m_pValueType->Clone();
	}

#line 76 "../../../Source/Core/AST/TrinaryExpr.nll"
	void TrinaryExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 78 "../../../Source/Core/AST/TrinaryExpr.nll"
		m_pFirstExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 79 "../../../Source/Core/AST/TrinaryExpr.nll"
		pOutputBuilder->m_sOut->Append(" ? ");
#line 80 "../../../Source/Core/AST/TrinaryExpr.nll"
		m_pSecondExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 81 "../../../Source/Core/AST/TrinaryExpr.nll"
		pOutputBuilder->m_sOut->Append(" : ");
#line 82 "../../../Source/Core/AST/TrinaryExpr.nll"
		m_pThirdExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

}

