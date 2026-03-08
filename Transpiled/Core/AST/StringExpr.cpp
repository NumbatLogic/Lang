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
	StringExpr* StringExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		Token* pToken = pTokenContainer->PeekExpect(pOffsetDatum, Token::Type::TOKEN_STRING);
		if (pToken == 0)
			return 0;
		pOffsetDatum->m_nOffset = pOffsetDatum->m_nOffset + 1;
		StringExpr* pStringExpr = new StringExpr();
		pStringExpr->m_eType = AST::Type::AST_STRING;
		pStringExpr->m_pFirstToken = pToken;
		NumbatLogic::StringExpr* __1742613754 = pStringExpr;
		pStringExpr = 0;
		return __1742613754;
	}

	void StringExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::STRING);
	}

	void StringExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out)
	{
		m_pFirstToken->Stringify(out->m_sOut);
	}

}

