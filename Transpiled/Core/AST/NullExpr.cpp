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
#line 0 "../../../Source/Core/AST/NullExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/NullExpr.nll"
#line 5 "../../../Source/Core/AST/NullExpr.nll"
	NullExpr::NullExpr()
	{
		m_eType = AST::Type::NULL_EXPR;
	}

	NullExpr* NullExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 14 "../../../Source/Core/AST/NullExpr.nll"
		Token* pNullToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_NULL);
		if (pNullToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 16 "../../../Source/Core/AST/NullExpr.nll"
			return 0;
		}
#line 17 "../../../Source/Core/AST/NullExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 19 "../../../Source/Core/AST/NullExpr.nll"
		NullExpr* pNullExpr = new NullExpr();
		pNullExpr->m_pFirstToken = pNullToken;
#line 22 "../../../Source/Core/AST/NullExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::NullExpr* __4021522189 = pNullExpr;
#line 23 "../../../Source/Core/AST/NullExpr.nll"
		pNullExpr = 0;
		if (pTempOffset) delete pTempOffset;
#line 23 "../../../Source/Core/AST/NullExpr.nll"
		return __4021522189;
	}

	void NullExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::NULL_VALUE);
	}

	void NullExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (eLanguage == AST::Language::CPP)
			pOutputBuilder->m_sOut->Append("0");
		else
			pOutputBuilder->m_sOut->Append("null");
	}

}

