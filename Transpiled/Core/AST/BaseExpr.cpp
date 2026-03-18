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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
	BaseExpr* BaseExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
		Token* pThisToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_BASE);
		if (pThisToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
			return 0;
		}
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
		BaseExpr* pBaseExpr = new BaseExpr();
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
		pBaseExpr->m_eType = AST::Type::BASE_EXPR;
		pBaseExpr->m_pFirstToken = pThisToken;
#line 21 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::BaseExpr* __3152999094 = pBaseExpr;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
		pBaseExpr = 0;
		if (pTempOffset) delete pTempOffset;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
		return __3152999094;
	}

	void BaseExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
		AST* pTestParent = m_pParent;
		while (true)
		{
			if (pTestParent == 0)
			{
				pValidator->AddError("this is not the child of a ClassDec???", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				return;
			}
#line 38 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
			if (pTestParent->m_eType == AST::Type::AST_CLASS_DECL)
				break;
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
			pTestParent = pTestParent->m_pParent;
		}
#line 44 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
		ClassDecl* pClassDecl = (ClassDecl*)(pTestParent);
		ClassDecl* pBaseClassDecl = pClassDecl->GetBaseClassDecl(pValidator);
#line 47 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
		if (pBaseClassDecl == 0)
		{
			pValidator->AddError("class does not have a base class!", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			return;
		}
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
		m_pValueType->m_pClassDecl = pClassDecl;
#line 55 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
		m_pBaseClassDecl = pBaseClassDecl;
	}

#line 60 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
	void BaseExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (eLanguage == AST::Language::CPP)
			m_pBaseClassDecl->m_pNameToken->Stringify(pOutputBuilder->m_sOut);
		else
			pOutputBuilder->m_sOut->Append("base");
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/BaseExpr.nll"
	BaseExpr::BaseExpr()
	{
		m_pBaseClassDecl = 0;
	}

}

