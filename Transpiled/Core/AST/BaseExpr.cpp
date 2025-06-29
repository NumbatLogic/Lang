#include "BaseExpr.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../ValueType.hpp"
#include "../Validator.hpp"
#include "ClassDecl.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class BaseExpr;
	class AST;
	class ClassDecl;
}
namespace NumbatLogic
{
	BaseExpr* BaseExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pThisToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_BASE);
		if (pThisToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		BaseExpr* pBaseExpr = new BaseExpr();
		pBaseExpr->m_eType = AST::Type::BASE_EXPR;
		pBaseExpr->m_pFirstToken = pThisToken;
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::BaseExpr* __500009809 = pBaseExpr;
		pBaseExpr = 0;
		if (pTempOffset) delete pTempOffset;
		return __500009809;
	}

	void BaseExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
		AST* pTestParent = m_pParent;
		while (true)
		{
			if (pTestParent == 0)
			{
				pValidator->AddError("this is not the child of a ClassDec???", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				return;
			}
			if (pTestParent->m_eType == AST::Type::AST_CLASS_DECL)
				break;
			pTestParent = pTestParent->m_pParent;
		}
		ClassDecl* pClassDecl = (ClassDecl*)(pTestParent);
		ClassDecl* pBaseClassDecl = pClassDecl->GetBaseClassDecl();
		if (pBaseClassDecl == 0)
		{
			pValidator->AddError("class does not have a base class!", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			return;
		}
		m_pValueType->m_pClassDecl = pClassDecl;
		m_pBaseClassDecl = pBaseClassDecl;
	}

	void BaseExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (eLanguage == AST::Language::CPP)
			m_pBaseClassDecl->m_pNameToken->Stringify(sOut);
		else
			sOut->Append("base");
	}

	BaseExpr::BaseExpr()
	{
		m_pBaseClassDecl = 0;
	}

}

