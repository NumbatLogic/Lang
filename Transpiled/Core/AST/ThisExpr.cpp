#include "ThisExpr.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../ValueType.hpp"
#include "../Validator.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class ThisExpr;
	class ValueType;
	class Validator;
	class ClassDecl;
	class OutputBuilder;
	class InternalString;
}
#line 1 "../../../Source/Core/AST/ThisExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/ThisExpr.nll"
#line 6 "../../../Source/Core/AST/ThisExpr.nll"
	ThisExpr* ThisExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pThisToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_THIS);
#line 11 "../../../Source/Core/AST/ThisExpr.nll"
		if (pThisToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 12 "../../../Source/Core/AST/ThisExpr.nll"
			return 0;
		}
#line 13 "../../../Source/Core/AST/ThisExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ThisExpr* pThisExpr = new ThisExpr();
#line 17 "../../../Source/Core/AST/ThisExpr.nll"
		pThisExpr->m_eType = AST::Type::THIS_EXPR;
#line 18 "../../../Source/Core/AST/ThisExpr.nll"
		pThisExpr->m_pFirstToken = pThisToken;
#line 20 "../../../Source/Core/AST/ThisExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ThisExpr* __1365567169 = pThisExpr;
#line 21 "../../../Source/Core/AST/ThisExpr.nll"
		pThisExpr = 0;
		if (pTempOffset) delete pTempOffset;
#line 21 "../../../Source/Core/AST/ThisExpr.nll"
		return __1365567169;
	}

#line 24 "../../../Source/Core/AST/ThisExpr.nll"
	void ThisExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 26 "../../../Source/Core/AST/ThisExpr.nll"
		m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
		AST* pTestParent = m_pParent;
#line 29 "../../../Source/Core/AST/ThisExpr.nll"
		while (true)
		{
#line 31 "../../../Source/Core/AST/ThisExpr.nll"
			if (pTestParent == 0)
			{
#line 33 "../../../Source/Core/AST/ThisExpr.nll"
				pValidator->AddError("this is not the child of a ClassDec???", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 34 "../../../Source/Core/AST/ThisExpr.nll"
				return;
			}
#line 37 "../../../Source/Core/AST/ThisExpr.nll"
			if (pTestParent->m_eType == AST::Type::AST_CLASS_DECL)
#line 38 "../../../Source/Core/AST/ThisExpr.nll"
				break;
#line 40 "../../../Source/Core/AST/ThisExpr.nll"
			pTestParent = pTestParent->m_pParent;
		}
#line 43 "../../../Source/Core/AST/ThisExpr.nll"
		m_pValueType->m_pClassDecl = (ClassDecl*)(pTestParent);
	}

#line 46 "../../../Source/Core/AST/ThisExpr.nll"
	void ThisExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 48 "../../../Source/Core/AST/ThisExpr.nll"
		pOutputBuilder->m_sOut->Append("this");
	}

}

