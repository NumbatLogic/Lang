#include "CharExpr.hpp"
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
	class CharExpr;
	class ValueType;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
	CharExpr* CharExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		Token* pToken = pTokenContainer->PeekExpect(pOffsetDatum, Token::Type::TOKEN_CHAR);
		if (pToken == 0)
			return 0;
		pOffsetDatum->m_nOffset = pOffsetDatum->m_nOffset + 1;
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
		CharExpr* pCharExpr = new CharExpr();
		pCharExpr->m_eType = AST::Type::AST_CHAR;
		pCharExpr->m_pFirstToken = pToken;
		NumbatLogic::CharExpr* __2615706591 = pCharExpr;
#line 15 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
		pCharExpr = 0;
#line 15 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
		return __2615706591;
	}

	void CharExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::CHAR);
	}

	void CharExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
	}

}

