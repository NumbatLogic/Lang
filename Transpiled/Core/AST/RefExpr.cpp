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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
	RefExpr* RefExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		Token* pRefToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_REF);
		if (pRefToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
			return 0;
		}
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pExpression == 0)
		{
			Console::Log("expected expresssion");
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 21 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
			return 0;
		}
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		RefExpr* pRefExpr = new RefExpr();
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		pRefExpr->m_eType = AST::Type::AST_REF_EXPR;
		pRefExpr->m_pFirstToken = pRefToken;
		pRefExpr->m_pExpression = pExpression;
		NumbatLogic::AST* __1929334319 = pExpression;
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		pExpression = 0;
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		pRefExpr->AddChild(__1929334319);
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::RefExpr* __1130235351 = pRefExpr;
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		pRefExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		return __1130235351;
	}

	void RefExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		if (m_pExpression->m_pValueType == 0)
		{
			InternalString* sTemp = new InternalString("ref expression has no value type");
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
#line 45 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
			return;
		}
#line 48 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		m_pValueType = m_pExpression->m_pValueType->Clone();
	}

	void RefExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (eLanguage == AST::Language::NLL || eLanguage == AST::Language::CS)
		{
			pOutputBuilder->m_sOut->Append("ref ");
		}
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
	RefExpr::RefExpr()
	{
		m_pExpression = 0;
	}

}

