#include "NumberExpr.hpp"
#include "AST.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../OffsetDatum.hpp"
#include "../ValueType.hpp"

namespace NumbatLogic
{
	class Token;
	class NumberExpr;
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
		{
			NumbatLogic::NumberExpr* __1682288392 = pNumberExpr;
			pNumberExpr = 0;
			return __1682288392;
		}
	}

	AST* NumberExpr::BaseClone()
	{
		NumberExpr* pNumberExpr = new NumberExpr(m_pFirstToken);
		{
			NumbatLogic::NumberExpr* __1682288392 = pNumberExpr;
			pNumberExpr = 0;
			return __1682288392;
		}
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

