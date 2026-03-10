#include "NumberExpr.hpp"
#include "AST.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../OffsetDatum.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"

namespace NumbatLogic
{
	class AST;
	class Token;
	class TokenContainer;
	class OffsetDatum;
	class NumberExpr;
	class ValueType;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/NumberExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/NumberExpr.nll"
#line 5 "../../../Source/Core/AST/NumberExpr.nll"
	NumberExpr::NumberExpr(Token* pFirstToken)
	{
#line 7 "../../../Source/Core/AST/NumberExpr.nll"
		m_eType = AST::Type::AST_NUMBER;
#line 8 "../../../Source/Core/AST/NumberExpr.nll"
		m_pFirstToken = pFirstToken;
	}

#line 11 "../../../Source/Core/AST/NumberExpr.nll"
	NumberExpr* NumberExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
#line 13 "../../../Source/Core/AST/NumberExpr.nll"
		Token* pToken = pTokenContainer->PeekExpect(pOffsetDatum, Token::Type::TOKEN_NUMBER);
#line 14 "../../../Source/Core/AST/NumberExpr.nll"
		if (pToken == 0)
#line 15 "../../../Source/Core/AST/NumberExpr.nll"
			return 0;
#line 16 "../../../Source/Core/AST/NumberExpr.nll"
		pOffsetDatum->m_nOffset = pOffsetDatum->m_nOffset + 1;
#line 17 "../../../Source/Core/AST/NumberExpr.nll"
		NumberExpr* pNumberExpr = new NumberExpr(pToken);
		NumbatLogic::NumberExpr* __3368034133 = pNumberExpr;
#line 18 "../../../Source/Core/AST/NumberExpr.nll"
		pNumberExpr = 0;
#line 18 "../../../Source/Core/AST/NumberExpr.nll"
		return __3368034133;
	}

#line 21 "../../../Source/Core/AST/NumberExpr.nll"
	AST* NumberExpr::BaseClone()
	{
#line 24 "../../../Source/Core/AST/NumberExpr.nll"
		NumberExpr* pNumberExpr = new NumberExpr(m_pFirstToken);
		NumbatLogic::NumberExpr* __3368099729 = pNumberExpr;
#line 25 "../../../Source/Core/AST/NumberExpr.nll"
		pNumberExpr = 0;
#line 25 "../../../Source/Core/AST/NumberExpr.nll"
		return __3368099729;
	}

#line 28 "../../../Source/Core/AST/NumberExpr.nll"
	void NumberExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 30 "../../../Source/Core/AST/NumberExpr.nll"
		m_pValueType = new ValueType(ValueType::Type::INT);
	}

#line 33 "../../../Source/Core/AST/NumberExpr.nll"
	void NumberExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 35 "../../../Source/Core/AST/NumberExpr.nll"
		m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
	}

}

