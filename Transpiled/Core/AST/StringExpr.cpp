#include "StringExpr.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../OffsetDatum.hpp"
#include "AST.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"

namespace NumbatLogic
{
	class AST;
	class Token;
	class TokenContainer;
	class OffsetDatum;
	class StringExpr;
	class ValueType;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/StringExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/StringExpr.nll"
#line 5 "../../../Source/Core/AST/StringExpr.nll"
	StringExpr* StringExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
#line 7 "../../../Source/Core/AST/StringExpr.nll"
		Token* pToken = pTokenContainer->PeekExpect(pOffsetDatum, Token::Type::TOKEN_STRING);
#line 8 "../../../Source/Core/AST/StringExpr.nll"
		if (pToken == 0)
#line 9 "../../../Source/Core/AST/StringExpr.nll"
			return 0;
#line 10 "../../../Source/Core/AST/StringExpr.nll"
		pOffsetDatum->m_nOffset = pOffsetDatum->m_nOffset + 1;
#line 12 "../../../Source/Core/AST/StringExpr.nll"
		StringExpr* pStringExpr = new StringExpr();
#line 13 "../../../Source/Core/AST/StringExpr.nll"
		pStringExpr->m_eType = AST::Type::AST_STRING;
#line 14 "../../../Source/Core/AST/StringExpr.nll"
		pStringExpr->m_pFirstToken = pToken;
		NumbatLogic::StringExpr* __1742613754 = pStringExpr;
#line 15 "../../../Source/Core/AST/StringExpr.nll"
		pStringExpr = 0;
#line 15 "../../../Source/Core/AST/StringExpr.nll"
		return __1742613754;
	}

#line 18 "../../../Source/Core/AST/StringExpr.nll"
	void StringExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 20 "../../../Source/Core/AST/StringExpr.nll"
		m_pValueType = new ValueType(ValueType::Type::STRING);
	}

#line 23 "../../../Source/Core/AST/StringExpr.nll"
	void StringExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 25 "../../../Source/Core/AST/StringExpr.nll"
		m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
	}

}

