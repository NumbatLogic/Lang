#include "NullExpr.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class NullExpr;
	class ValueType;
	class OutputBuilder;
	class InternalString;
}
#line 1 "../../../Source/Core/AST/NullExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/NullExpr.nll"
#line 6 "../../../Source/Core/AST/NullExpr.nll"
	NullExpr::NullExpr()
	{
#line 8 "../../../Source/Core/AST/NullExpr.nll"
		m_eType = AST::Type::NULL_EXPR;
	}

#line 11 "../../../Source/Core/AST/NullExpr.nll"
	NullExpr* NullExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pNullToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_NULL);
#line 16 "../../../Source/Core/AST/NullExpr.nll"
		if (pNullToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 17 "../../../Source/Core/AST/NullExpr.nll"
			return 0;
		}
#line 18 "../../../Source/Core/AST/NullExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		NullExpr* pNullExpr = new NullExpr();
#line 21 "../../../Source/Core/AST/NullExpr.nll"
		pNullExpr->m_pFirstToken = pNullToken;
#line 23 "../../../Source/Core/AST/NullExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::NullExpr* __4021522189 = pNullExpr;
#line 24 "../../../Source/Core/AST/NullExpr.nll"
		pNullExpr = 0;
		if (pTempOffset) delete pTempOffset;
#line 24 "../../../Source/Core/AST/NullExpr.nll"
		return __4021522189;
	}

#line 27 "../../../Source/Core/AST/NullExpr.nll"
	void NullExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 29 "../../../Source/Core/AST/NullExpr.nll"
		m_pValueType = new ValueType(ValueType::Type::NULL_VALUE);
	}

#line 32 "../../../Source/Core/AST/NullExpr.nll"
	void NullExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 34 "../../../Source/Core/AST/NullExpr.nll"
		if (eLanguage == AST::Language::CPP)
#line 35 "../../../Source/Core/AST/NullExpr.nll"
			pOutputBuilder->m_sOut->Append("0");
		else
#line 37 "../../../Source/Core/AST/NullExpr.nll"
			pOutputBuilder->m_sOut->Append("null");
	}

}

