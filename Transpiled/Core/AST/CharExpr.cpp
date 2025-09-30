#include "CharExpr.hpp"
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
	class CharExpr;
	class ValueType;
}
namespace NumbatLogic
{
	CharExpr* CharExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		Token* pToken = pTokenContainer->PeekExpect(pOffsetDatum, Token::Type::TOKEN_CHAR);
		if (pToken == 0)
			return 0;
		pOffsetDatum->m_nOffset = pOffsetDatum->m_nOffset + 1;
		CharExpr* pCharExpr = new CharExpr();
		pCharExpr->m_eType = AST::Type::AST_CHAR;
		pCharExpr->m_pFirstToken = pToken;
		NumbatLogic::CharExpr* __3944088616 = pCharExpr;
		pCharExpr = 0;
		return __3944088616;
	}

	void CharExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::CHAR);
	}

	void CharExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		m_pFirstToken->Stringify(sOut);
	}

}

