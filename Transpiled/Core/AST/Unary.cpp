#include "Unary.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class AST;
	class Unary;
	class InternalString;
}
namespace NumbatLogic
{
	Unary* Unary::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pToken = pTokenContainer->Peek(pTempOffset);
		if (pToken == 0 || pToken->m_eType != Token::Type::TOKEN_MINUS && pToken->m_eType != Token::Type::TOKEN_BANG && pToken->m_eType != Token::Type::TOKEN_PLUS_PLUS && pToken->m_eType != Token::Type::TOKEN_MINUS_MINUS && pToken->m_eType != Token::Type::TOKEN_TILDE)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		Unary* pUnary = new Unary();
		pUnary->m_eType = AST::Type::AST_UNARY;
		pUnary->m_pFirstToken = pToken;
		pUnary->m_pExpression = pExpression;
		{
			NumbatLogic::AST* __1067118945 = pExpression;
			pExpression = 0;
			pUnary->AddChild(__1067118945);
		}
		pOffsetDatum->Set(pTempOffset);
		{
			NumbatLogic::Unary* __2316923926 = pUnary;
			pUnary = 0;
			{
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				return __2316923926;
			}
		}
	}

	void Unary::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		if (m_pExpression->m_pValueType == 0)
		{
			InternalString* sTemp = new InternalString("expression did not validate?? ");
			m_pExpression->StringifyType(sTemp);
			pValidator->AddError(sTemp->GetExternalString(), m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			{
				if (sTemp) delete sTemp;
				return;
			}
		}
		m_pValueType = m_pExpression->m_pValueType->Clone();
	}

	void Unary::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		m_pFirstToken->Stringify(sOut);
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
	}

	Unary::Unary()
	{
		m_pExpression = 0;
	}

}

