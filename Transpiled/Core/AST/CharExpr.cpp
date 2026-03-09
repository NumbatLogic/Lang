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
#line 1 "../../../Source/Core/AST/CharExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/CharExpr.nll"
#line 6 "../../../Source/Core/AST/CharExpr.nll"
	CharExpr* CharExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		Token* pToken = pTokenContainer->PeekExpect(pOffsetDatum, Token::Type::TOKEN_CHAR);
#line 9 "../../../Source/Core/AST/CharExpr.nll"
		if (pToken == 0)
#line 10 "../../../Source/Core/AST/CharExpr.nll"
			return 0;
#line 11 "../../../Source/Core/AST/CharExpr.nll"
		pOffsetDatum->m_nOffset = pOffsetDatum->m_nOffset + 1;
		CharExpr* pCharExpr = new CharExpr();
#line 14 "../../../Source/Core/AST/CharExpr.nll"
		pCharExpr->m_eType = AST::Type::AST_CHAR;
#line 15 "../../../Source/Core/AST/CharExpr.nll"
		pCharExpr->m_pFirstToken = pToken;
		NumbatLogic::CharExpr* __2615706591 = pCharExpr;
#line 16 "../../../Source/Core/AST/CharExpr.nll"
		pCharExpr = 0;
#line 16 "../../../Source/Core/AST/CharExpr.nll"
		return __2615706591;
	}

#line 19 "../../../Source/Core/AST/CharExpr.nll"
	void CharExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 21 "../../../Source/Core/AST/CharExpr.nll"
		m_pValueType = new ValueType(ValueType::Type::CHAR);
	}

#line 24 "../../../Source/Core/AST/CharExpr.nll"
	void CharExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 26 "../../../Source/Core/AST/CharExpr.nll"
		m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
	}

}

