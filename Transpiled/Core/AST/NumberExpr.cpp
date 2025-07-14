#include "NumberExpr.hpp"
#include "AST.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../OffsetDatum.hpp"
#include "../ValueType.hpp"

namespace NumbatLogic
{
	class NumberExpr;
	class AST;
	class Token;
	class TokenContainer;
	class Token;
	class OffsetDatum;
	class NumberExpr;
	class ValueType;
}
namespace NumbatLogic
{
	NumberExpr::NumberExpr(Token* pFirstToken)
	{
		m_eType = AST::Type::AST_NUMBER;
		m_pFirstToken = pFirstToken;
	}

	NumberExpr* NumberExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		Token* pToken = pTokenContainer->PeekExpect(pOffsetDatum, Token::Type::TOKEN_NUMBER);
		if (pToken == 0)
			return 0;
		pOffsetDatum->m_nOffset = pOffsetDatum->m_nOffset + 1;
		NumberExpr* pNumberExpr = new NumberExpr(pToken);
		NumbatLogic::NumberExpr* __269765533 = pNumberExpr;
		pNumberExpr = 0;
		return __269765533;
	}

	AST* NumberExpr::BaseClone()
	{
		NumberExpr* pNumberExpr = new NumberExpr(m_pFirstToken);
		NumbatLogic::NumberExpr* __2215916372 = pNumberExpr;
		pNumberExpr = 0;
		return __2215916372;
	}

	void NumberExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::INT);
	}

	void NumberExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		m_pFirstToken->Stringify(sOut);
	}

}

