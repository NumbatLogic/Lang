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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
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
		NumbatLogic::NumberExpr* __3368034133 = pNumberExpr;
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
		pNumberExpr = 0;
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
		return __3368034133;
	}

	AST* NumberExpr::BaseClone()
	{
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
		NumberExpr* pNumberExpr = new NumberExpr(m_pFirstToken);
		NumbatLogic::NumberExpr* __3368099729 = pNumberExpr;
#line 25 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
		pNumberExpr = 0;
#line 25 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
		return __3368099729;
	}

	void NumberExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::INT);
	}

	void NumberExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
	}

}

