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
		Token* pToken = pTokenContainer->PeekExpect(pOffsetDatum, Token::Type::TOKEN_STRING);
		if (pToken == 0)
			return 0;
		pOffsetDatum->m_nOffset = pOffsetDatum->m_nOffset + 1;
#line 12 "../../../Source/Core/AST/StringExpr.nll"
		StringExpr* pStringExpr = new StringExpr();
		pStringExpr->m_eType = AST::Type::AST_STRING;
		pStringExpr->m_pFirstToken = pToken;
		NumbatLogic::StringExpr* __1742613754 = pStringExpr;
#line 15 "../../../Source/Core/AST/StringExpr.nll"
		pStringExpr = 0;
#line 15 "../../../Source/Core/AST/StringExpr.nll"
		return __1742613754;
	}

	void StringExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::STRING);
	}

	void StringExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
	}

}

