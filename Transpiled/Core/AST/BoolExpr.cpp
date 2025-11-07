#include "BoolExpr.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../OffsetDatum.hpp"
#include "AST.hpp"
#include "../ValueType.hpp"

namespace NumbatLogic
{
	class AST;
	class Token;
	class TokenContainer;
	class OffsetDatum;
	class BoolExpr;
	class ValueType;
}
namespace NumbatLogic
{
	BoolExpr* BoolExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		Token* pToken = pTokenContainer->Peek(pOffsetDatum);
		if (pToken == 0 || (pToken->m_eType != Token::Type::TOKEN_KEYWORD_TRUE && pToken->m_eType != Token::Type::TOKEN_KEYWORD_FALSE))
			return 0;
		pOffsetDatum->m_nOffset = pOffsetDatum->m_nOffset + 1;
		BoolExpr* pBoolExpr = new BoolExpr();
		pBoolExpr->m_eType = AST::Type::AST_BOOL_EXPR;
		pBoolExpr->m_pFirstToken = pToken;
		NumbatLogic::BoolExpr* __1361960776 = pBoolExpr;
		pBoolExpr = 0;
		return __1361960776;
	}

	void BoolExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::BOOL);
	}

	void BoolExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		m_pFirstToken->Stringify(sOut);
	}

}

