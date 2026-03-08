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
#line 1 "../../../Source/Core/AST/RefExpr.nll"
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
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
			return 0;
		}
		RefExpr* pRefExpr = new RefExpr();
		pRefExpr->m_eType = AST::Type::AST_REF_EXPR;
		pRefExpr->m_pFirstToken = pRefToken;
		pRefExpr->m_pExpression = pExpression;
		NumbatLogic::AST* __1929334319 = pExpression;
		pExpression = 0;
		pRefExpr->AddChild(__1929334319);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::RefExpr* __1130235351 = pRefExpr;
		pRefExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
		return __1130235351;
	}

	void RefExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		if (m_pExpression->m_pValueType == 0)
		{
			InternalString* sTemp = new InternalString("ref expression has no value type");
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
			return;
		}
		m_pValueType = m_pExpression->m_pValueType->Clone();
	}

	void RefExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out)
	{
		if (eLanguage == AST::Language::NLL || eLanguage == AST::Language::CS)
		{
			out->m_sOut->Append("ref ");
		}
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, out);
	}

	RefExpr::RefExpr()
	{
		m_pExpression = 0;
	}

}

