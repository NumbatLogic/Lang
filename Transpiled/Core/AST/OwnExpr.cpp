#include "OwnExpr.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "TypeRef.hpp"
#include "../OutputBuilder.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Console;
	class Assert;
	class OwnExpr;
	class Validator;
	class ValueType;
	class InternalString;
	class TypeRef;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
	OwnExpr* OwnExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		Token* pOwnToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_OWN);
		if (pOwnToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
			return 0;
		}
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pExpression == 0)
		{
			Console::Log("expected expresssion");
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 21 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
			return 0;
		}
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		OwnExpr* pOwnExpr = new OwnExpr();
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		pOwnExpr->m_eType = AST::Type::AST_OWN_EXP;
		pOwnExpr->m_pFirstToken = pOwnToken;
		pOwnExpr->m_pExpression = pExpression;
		NumbatLogic::AST* __1929334319 = pExpression;
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		pExpression = 0;
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		pOwnExpr->AddChild(__1929334319);
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::OwnExpr* __4071014218 = pOwnExpr;
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		pOwnExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		return __4071014218;
	}

	void OwnExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		if (m_pExpression->m_pValueType == 0)
		{
			pValidator->AddError("Unable to determine right side of own", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
#line 45 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		if (m_pExpression->m_pValueType->m_eType != ValueType::Type::CLASS_DECL_VALUE && m_pExpression->m_pValueType->m_eType != ValueType::Type::GENERIC_TYPE_DECL_VALUE)
		{
			InternalString* sError = new InternalString("Expected right side of own to be a CLASS_DECL_VALUE or GENERIC_TYPE_DECL_VALUE, got: ");
			m_pExpression->m_pValueType->StringifyType(sError);
			pValidator->AddError(sError->GetExternalString(), m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			if (sError) delete sError;
#line 50 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
			return;
		}
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		if (m_pExpression->m_pValueType->m_ePointerType != TypeRef::PointerType::TRANSITON)
		{
			pValidator->AddError("Expected right side of own to be a TRANSITON type", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
#line 59 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		m_pValueType = m_pExpression->m_pValueType->Clone();
		m_pValueType->m_ePointerType = TypeRef::PointerType::OWNED_PREASSSIGN;
	}

	void OwnExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (eLanguage == AST::Language::NLL)
		{
			pOutputBuilder->m_sOut->Append("own ");
		}
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
	OwnExpr::OwnExpr()
	{
		m_pExpression = 0;
	}

}

