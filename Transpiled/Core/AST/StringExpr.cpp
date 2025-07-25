#include "StringExpr.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../OffsetDatum.hpp"
#include "AST.hpp"
#include "../ValueType.hpp"

namespace NumbatLogic
{
	class Token;
	class TokenContainer;
	class OffsetDatum;
	class StringExpr;
	class AST;
	class ValueType;
}
namespace NumbatLogic
{
	StringExpr* StringExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		Token* pToken = pTokenContainer->PeekExpect(pOffsetDatum, Token::Type::TOKEN_STRING);
		if (pToken == 0)
			return 0;
		pOffsetDatum->m_nOffset = pOffsetDatum->m_nOffset + 1;
		StringExpr* pStringExpr = new StringExpr();
		pStringExpr->m_eType = AST::Type::AST_STRING;
		pStringExpr->m_pFirstToken = pToken;
		NumbatLogic::StringExpr* __3984245982 = pStringExpr;
		pStringExpr = 0;
		return __3984245982;
	}

	void StringExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::STRING);
	}

	void StringExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		m_pFirstToken->Stringify(sOut);
	}

}

