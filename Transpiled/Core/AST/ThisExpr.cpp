#include "ThisExpr.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../ValueType.hpp"
#include "../Validator.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class ThisExpr;
	class AST;
	class ClassDecl;
}
namespace NumbatLogic
{
	ThisExpr* ThisExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pThisToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_THIS);
		if (pThisToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ThisExpr* pThisExpr = new ThisExpr();
		pThisExpr->m_eType = AST::Type::THIS_EXPR;
		pThisExpr->m_pFirstToken = pThisToken;
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ThisExpr* __1209978893 = pThisExpr;
		pThisExpr = 0;
		if (pTempOffset) delete pTempOffset;
		return __1209978893;
	}

	void ThisExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
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
		m_pValueType->m_pClassDecl = (ClassDecl*)(pTestParent);
	}

	void ThisExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		sOut->Append("this");
	}

}

