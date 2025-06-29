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

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class AST;
	class OwnExpr;
	class InternalString;
}
namespace NumbatLogic
{
	OwnExpr* OwnExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pOwnToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_OWN);
		if (pOwnToken == 0)
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
		OwnExpr* pOwnExpr = new OwnExpr();
		pOwnExpr->m_eType = AST::Type::AST_OWN_EXP;
		pOwnExpr->m_pFirstToken = pOwnToken;
		pOwnExpr->m_pExpression = pExpression;
		NumbatLogic::AST* __2637546178 = pExpression;
		pExpression = 0;
		pOwnExpr->AddChild(__2637546178);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::OwnExpr* __2951986774 = pOwnExpr;
		pOwnExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
		return __2951986774;
	}

	void OwnExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		if (m_pExpression->m_pValueType == 0)
		{
			pValidator->AddError("Unable to determine right side of own", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
		if (m_pExpression->m_pValueType->m_eType != ValueType::Type::CLASS_DECL_VALUE && m_pExpression->m_pValueType->m_eType != ValueType::Type::GENERIC_TYPE_DECL_VALUE)
		{
			InternalString* sError = new InternalString("Expected right side of own to be a CLASS_DECL_VALUE or GENERIC_TYPE_DECL_VALUE, got: ");
			m_pExpression->m_pValueType->StringifyType(sError);
			pValidator->AddError(sError->GetExternalString(), m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			if (sError) delete sError;
			return;
		}
		if (m_pExpression->m_pValueType->m_ePointerType != TypeRef::PointerType::TRANSITON)
		{
			pValidator->AddError("Expected right side of own to be a TRANSITON type", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
		m_pValueType = m_pExpression->m_pValueType->Clone();
		m_pValueType->m_ePointerType = TypeRef::PointerType::OWNED_PREASSSIGN;
	}

	void OwnExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (eLanguage == AST::Language::NLL)
		{
			sOut->Append("own ");
		}
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
	}

	OwnExpr::OwnExpr()
	{
		m_pExpression = 0;
	}

}

