#include "TrinaryExpr.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../TokenContainer.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Token.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class AST;
	class Token;
	class TrinaryExpr;
}
namespace NumbatLogic
{
	TrinaryExpr::TrinaryExpr()
	{
		m_pFirstExpression = 0;
		m_pSecondExpression = 0;
		m_pThirdExpression = 0;
		m_eType = AST::Type::AST_DISOWN_EXP;
	}

	TrinaryExpr* TrinaryExpr::Create(AST* pFirstExpressionTransition, TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AST* pFirstExpression = pFirstExpressionTransition;
		AST* pSecondExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pSecondExpression == 0)
		{
			Console::Log("expected second expresssion");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pFirstExpression) delete pFirstExpression;
			if (pSecondExpression) delete pSecondExpression;
			return 0;
		}
		Token* pColonToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COLON);
		if (pColonToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pFirstExpression) delete pFirstExpression;
			if (pSecondExpression) delete pSecondExpression;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
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
			return 0;
		}
		TrinaryExpr* pTrinaryExpr = new TrinaryExpr();
		pTrinaryExpr->m_pFirstExpression = pFirstExpression;
		pTrinaryExpr->m_pSecondExpression = pSecondExpression;
		pTrinaryExpr->m_pThirdExpression = pThirdExpression;
		NumbatLogic::AST* __1176577974 = pFirstExpression;
		pFirstExpression = 0;
		pTrinaryExpr->AddChild(__1176577974);
		NumbatLogic::AST* __2317218345 = pSecondExpression;
		pSecondExpression = 0;
		pTrinaryExpr->AddChild(__2317218345);
		NumbatLogic::AST* __2588391620 = pThirdExpression;
		pThirdExpression = 0;
		pTrinaryExpr->AddChild(__2588391620);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::TrinaryExpr* __1659060397 = pTrinaryExpr;
		pTrinaryExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pFirstExpression) delete pFirstExpression;
		if (pSecondExpression) delete pSecondExpression;
		if (pThirdExpression) delete pThirdExpression;
		return __1659060397;
	}

	void TrinaryExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		if (m_pThirdExpression->m_pValueType == 0)
		{
			pValidator->AddError("Unknown ValueType of 2nd expression", m_pSecondExpression->m_pFirstToken->m_sFileName, m_pSecondExpression->m_pFirstToken->m_nLine, m_pSecondExpression->m_pFirstToken->m_nColumn);
			return;
		}
		if (m_pThirdExpression->m_pValueType == 0)
		{
			pValidator->AddError("Unknown ValueType of 3rd expression", m_pThirdExpression->m_pFirstToken->m_sFileName, m_pThirdExpression->m_pFirstToken->m_nLine, m_pThirdExpression->m_pFirstToken->m_nColumn);
			return;
		}
		m_pValueType = m_pSecondExpression->m_pValueType->Clone();
	}

	void TrinaryExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		m_pFirstExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->Append(" ? ");
		m_pSecondExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->Append(" : ");
		m_pThirdExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
	}

}

