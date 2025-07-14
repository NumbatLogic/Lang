#include "NullExpr.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../ValueType.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class NullExpr;
	class ValueType;
	class InternalString;
}
namespace NumbatLogic
{
	NullExpr::NullExpr()
	{
		m_eType = AST::Type::NULL_EXPR;
	}

	NullExpr* NullExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pNullToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_NULL);
		if (pNullToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		NullExpr* pNullExpr = new NullExpr();
		pNullExpr->m_pFirstToken = pNullToken;
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::NullExpr* __2037129396 = pNullExpr;
		pNullExpr = 0;
		if (pTempOffset) delete pTempOffset;
		return __2037129396;
	}

	void NullExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::NULL_VALUE);
	}

	void NullExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (eLanguage == AST::Language::CPP)
			sOut->Append("0");
		else
			sOut->Append("null");
	}

}

