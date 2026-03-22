#include "TrinaryExpr.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../TokenContainer.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "../Token.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"

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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
	TrinaryExpr::TrinaryExpr()
	{
		m_pFirstExpression = 0;
		m_pSecondExpression = 0;
		m_pThirdExpression = 0;
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		m_eType = AST::Type::AST_DISOWN_EXP;
	}

	TrinaryExpr* TrinaryExpr::Create(AST* pFirstExpressionTransition, TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		AST* pFirstExpression = pFirstExpressionTransition;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		AST* pSecondExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pSecondExpression == 0)
		{
			Console::Log("expected second expresssion");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pFirstExpression) delete pFirstExpression;
			if (pSecondExpression) delete pSecondExpression;
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			return 0;
		}
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		Token* pColonToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COLON);
		if (pColonToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pFirstExpression) delete pFirstExpression;
			if (pSecondExpression) delete pSecondExpression;
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			return 0;
		}
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 34 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		AST* pThirdExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pThirdExpression == 0)
		{
			Console::Log("expected second expresssion");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pFirstExpression) delete pFirstExpression;
			if (pSecondExpression) delete pSecondExpression;
			if (pThirdExpression) delete pThirdExpression;
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
			return 0;
		}
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		TrinaryExpr* pTrinaryExpr = new TrinaryExpr();
#line 45 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		pTrinaryExpr->m_pFirstExpression = pFirstExpression;
		pTrinaryExpr->m_pSecondExpression = pSecondExpression;
		pTrinaryExpr->m_pThirdExpression = pThirdExpression;
		NumbatLogic::AST* __2029364893 = pFirstExpression;
		pFirstExpression = 0;
#line 49 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		pTrinaryExpr->AddChild(__2029364893);
		NumbatLogic::AST* __45120503 = pSecondExpression;
#line 50 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		pSecondExpression = 0;
#line 50 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		pTrinaryExpr->AddChild(__45120503);
		NumbatLogic::AST* __777254731 = pThirdExpression;
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		pThirdExpression = 0;
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		pTrinaryExpr->AddChild(__777254731);
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::TrinaryExpr* __2348216585 = pTrinaryExpr;
#line 54 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		pTrinaryExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pFirstExpression) delete pFirstExpression;
		if (pSecondExpression) delete pSecondExpression;
		if (pThirdExpression) delete pThirdExpression;
#line 54 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		return __2348216585;
	}

	void TrinaryExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
#line 61 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		if (m_pSecondExpression->m_pValueType == 0)
		{
			pValidator->AddError("Unknown ValueType of 2nd expression", m_pSecondExpression->m_pFirstToken->m_sFileName, m_pSecondExpression->m_pFirstToken->m_nLine, m_pSecondExpression->m_pFirstToken->m_nColumn);
			return;
		}
#line 67 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		if (m_pThirdExpression->m_pValueType == 0)
		{
			pValidator->AddError("Unknown ValueType of 3rd expression", m_pThirdExpression->m_pFirstToken->m_sFileName, m_pThirdExpression->m_pFirstToken->m_nLine, m_pThirdExpression->m_pFirstToken->m_nColumn);
			return;
		}
#line 73 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		m_pValueType = m_pSecondExpression->m_pValueType->Clone();
	}

	void TrinaryExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		m_pFirstExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		pOutputBuilder->m_sOut->Append(" ? ");
		m_pSecondExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		pOutputBuilder->m_sOut->Append(" : ");
		m_pThirdExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

}

