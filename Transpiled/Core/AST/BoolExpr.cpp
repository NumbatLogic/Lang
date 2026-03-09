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
#line 1 "../../../Source/Core/AST/BoolExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/BoolExpr.nll"
#line 6 "../../../Source/Core/AST/BoolExpr.nll"
	BoolExpr* BoolExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		Token* pToken = pTokenContainer->Peek(pOffsetDatum);
#line 9 "../../../Source/Core/AST/BoolExpr.nll"
		if (pToken == 0 || (pToken->m_eType != Token::Type::TOKEN_KEYWORD_TRUE && pToken->m_eType != Token::Type::TOKEN_KEYWORD_FALSE))
#line 10 "../../../Source/Core/AST/BoolExpr.nll"
			return 0;
#line 12 "../../../Source/Core/AST/BoolExpr.nll"
		pOffsetDatum->m_nOffset = pOffsetDatum->m_nOffset + 1;
		BoolExpr* pBoolExpr = new BoolExpr();
#line 15 "../../../Source/Core/AST/BoolExpr.nll"
		pBoolExpr->m_eType = AST::Type::AST_BOOL_EXPR;
#line 16 "../../../Source/Core/AST/BoolExpr.nll"
		pBoolExpr->m_pFirstToken = pToken;
		NumbatLogic::BoolExpr* __2520519956 = pBoolExpr;
#line 17 "../../../Source/Core/AST/BoolExpr.nll"
		pBoolExpr = 0;
#line 17 "../../../Source/Core/AST/BoolExpr.nll"
		return __2520519956;
	}

#line 20 "../../../Source/Core/AST/BoolExpr.nll"
	void BoolExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 22 "../../../Source/Core/AST/BoolExpr.nll"
		m_pValueType = new ValueType(ValueType::Type::BOOL);
	}

#line 25 "../../../Source/Core/AST/BoolExpr.nll"
	void BoolExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 27 "../../../Source/Core/AST/BoolExpr.nll"
		m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
	}

}

