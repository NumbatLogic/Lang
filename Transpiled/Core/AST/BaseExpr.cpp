#include "BaseExpr.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../ValueType.hpp"
#include "../Validator.hpp"
#include "ClassDecl.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class BaseExpr;
	class ValueType;
	class Validator;
	class ClassDecl;
	class OutputBuilder;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/BaseExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/BaseExpr.nll"
#line 7 "../../../Source/Core/AST/BaseExpr.nll"
	BaseExpr* BaseExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pThisToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_BASE);
#line 12 "../../../Source/Core/AST/BaseExpr.nll"
		if (pThisToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 13 "../../../Source/Core/AST/BaseExpr.nll"
			return 0;
		}
#line 14 "../../../Source/Core/AST/BaseExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		BaseExpr* pBaseExpr = new BaseExpr();
#line 18 "../../../Source/Core/AST/BaseExpr.nll"
		pBaseExpr->m_eType = AST::Type::BASE_EXPR;
#line 19 "../../../Source/Core/AST/BaseExpr.nll"
		pBaseExpr->m_pFirstToken = pThisToken;
#line 21 "../../../Source/Core/AST/BaseExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::BaseExpr* __3152999094 = pBaseExpr;
#line 22 "../../../Source/Core/AST/BaseExpr.nll"
		pBaseExpr = 0;
		if (pTempOffset) delete pTempOffset;
#line 22 "../../../Source/Core/AST/BaseExpr.nll"
		return __3152999094;
	}

#line 25 "../../../Source/Core/AST/BaseExpr.nll"
	void BaseExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 27 "../../../Source/Core/AST/BaseExpr.nll"
		m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
		AST* pTestParent = m_pParent;
#line 30 "../../../Source/Core/AST/BaseExpr.nll"
		while (true)
		{
#line 32 "../../../Source/Core/AST/BaseExpr.nll"
			if (pTestParent == 0)
			{
#line 34 "../../../Source/Core/AST/BaseExpr.nll"
				pValidator->AddError("this is not the child of a ClassDec???", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 35 "../../../Source/Core/AST/BaseExpr.nll"
				return;
			}
#line 38 "../../../Source/Core/AST/BaseExpr.nll"
			if (pTestParent->m_eType == AST::Type::AST_CLASS_DECL)
#line 39 "../../../Source/Core/AST/BaseExpr.nll"
				break;
#line 41 "../../../Source/Core/AST/BaseExpr.nll"
			pTestParent = pTestParent->m_pParent;
		}
		ClassDecl* pClassDecl = (ClassDecl*)(pTestParent);
		ClassDecl* pBaseClassDecl = pClassDecl->GetBaseClassDecl(pValidator);
#line 47 "../../../Source/Core/AST/BaseExpr.nll"
		if (pBaseClassDecl == 0)
		{
#line 49 "../../../Source/Core/AST/BaseExpr.nll"
			pValidator->AddError("class does not have a base class!", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 50 "../../../Source/Core/AST/BaseExpr.nll"
			return;
		}
#line 53 "../../../Source/Core/AST/BaseExpr.nll"
		m_pValueType->m_pClassDecl = pClassDecl;
#line 55 "../../../Source/Core/AST/BaseExpr.nll"
		m_pBaseClassDecl = pBaseClassDecl;
	}

#line 60 "../../../Source/Core/AST/BaseExpr.nll"
	void BaseExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 62 "../../../Source/Core/AST/BaseExpr.nll"
		if (eLanguage == AST::Language::CPP)
#line 63 "../../../Source/Core/AST/BaseExpr.nll"
			m_pBaseClassDecl->m_pNameToken->Stringify(pOutputBuilder->m_sOut);
		else
#line 65 "../../../Source/Core/AST/BaseExpr.nll"
			pOutputBuilder->m_sOut->Append("base");
	}

#line 3 "../../../Source/Core/AST/BaseExpr.nll"
	BaseExpr::BaseExpr()
	{
		m_pBaseClassDecl = 0;
	}

}

