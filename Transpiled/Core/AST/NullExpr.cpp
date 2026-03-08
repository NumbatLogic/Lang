#include "NullExpr.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class NullExpr;
	class ValueType;
	class OutputBuilder;
	class InternalString;
}
#line 1 "../../../Source/Core/AST/NullExpr.nll"
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
		NumbatLogic::NullExpr* __4021522189 = pNullExpr;
		pNullExpr = 0;
		if (pTempOffset) delete pTempOffset;
		return __4021522189;
	}

	void NullExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::NULL_VALUE);
	}

	void NullExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out)
	{
		if (eLanguage == AST::Language::CPP)
			out->m_sOut->Append("0");
		else
			out->m_sOut->Append("null");
	}

}

