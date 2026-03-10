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
#line 0 "../../../Source/Core/AST/ThisExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ThisExpr.nll"
#line 5 "../../../Source/Core/AST/ThisExpr.nll"
	ThisExpr* ThisExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pThisToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_THIS);
#line 10 "../../../Source/Core/AST/ThisExpr.nll"
		if (pThisToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 11 "../../../Source/Core/AST/ThisExpr.nll"
			return 0;
		}
#line 12 "../../../Source/Core/AST/ThisExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ThisExpr* pThisExpr = new ThisExpr();
#line 16 "../../../Source/Core/AST/ThisExpr.nll"
		pThisExpr->m_eType = AST::Type::THIS_EXPR;
#line 17 "../../../Source/Core/AST/ThisExpr.nll"
		pThisExpr->m_pFirstToken = pThisToken;
#line 19 "../../../Source/Core/AST/ThisExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ThisExpr* __1365567169 = pThisExpr;
#line 20 "../../../Source/Core/AST/ThisExpr.nll"
		pThisExpr = 0;
		if (pTempOffset) delete pTempOffset;
#line 20 "../../../Source/Core/AST/ThisExpr.nll"
		return __1365567169;
	}

#line 23 "../../../Source/Core/AST/ThisExpr.nll"
	void ThisExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 25 "../../../Source/Core/AST/ThisExpr.nll"
		m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
		AST* pTestParent = m_pParent;
#line 28 "../../../Source/Core/AST/ThisExpr.nll"
		while (true)
		{
#line 30 "../../../Source/Core/AST/ThisExpr.nll"
			if (pTestParent == 0)
			{
#line 32 "../../../Source/Core/AST/ThisExpr.nll"
				pValidator->AddError("this is not the child of a ClassDec???", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 33 "../../../Source/Core/AST/ThisExpr.nll"
				return;
			}
#line 36 "../../../Source/Core/AST/ThisExpr.nll"
			if (pTestParent->m_eType == AST::Type::AST_CLASS_DECL)
#line 37 "../../../Source/Core/AST/ThisExpr.nll"
				break;
#line 39 "../../../Source/Core/AST/ThisExpr.nll"
			pTestParent = pTestParent->m_pParent;
		}
#line 42 "../../../Source/Core/AST/ThisExpr.nll"
		m_pValueType->m_pClassDecl = (ClassDecl*)(pTestParent);
	}

#line 45 "../../../Source/Core/AST/ThisExpr.nll"
	void ThisExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 47 "../../../Source/Core/AST/ThisExpr.nll"
		pOutputBuilder->m_sOut->Append("this");
	}

}

