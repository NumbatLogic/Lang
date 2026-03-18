#include "BoolExpr.hpp"
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
	class BoolExpr;
	class ValueType;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/BoolExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/BoolExpr.nll"
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/BoolExpr.nll"
	BoolExpr* BoolExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		Token* pToken = pTokenContainer->Peek(pOffsetDatum);
		if (pToken == 0 || (pToken->m_eType != Token::Type::TOKEN_KEYWORD_TRUE && pToken->m_eType != Token::Type::TOKEN_KEYWORD_FALSE))
			return 0;
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/BoolExpr.nll"
		pOffsetDatum->m_nOffset = pOffsetDatum->m_nOffset + 1;
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/BoolExpr.nll"
		BoolExpr* pBoolExpr = new BoolExpr();
		pBoolExpr->m_eType = AST::Type::AST_BOOL_EXPR;
		pBoolExpr->m_pFirstToken = pToken;
		NumbatLogic::BoolExpr* __2520519956 = pBoolExpr;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/BoolExpr.nll"
		pBoolExpr = 0;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/BoolExpr.nll"
		return __2520519956;
	}

	void BoolExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::BOOL);
	}

	void BoolExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
	}

}

