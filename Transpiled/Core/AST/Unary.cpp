#include "Unary.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Unary;
	class InternalString;
	class Validator;
	class ValueType;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
	Unary* Unary::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
		Token* pToken = pTokenContainer->Peek(pTempOffset);
		if (pToken == 0 || pToken->m_eType != Token::Type::TOKEN_MINUS && pToken->m_eType != Token::Type::TOKEN_BANG && pToken->m_eType != Token::Type::TOKEN_PLUS_PLUS && pToken->m_eType != Token::Type::TOKEN_MINUS_MINUS && pToken->m_eType != Token::Type::TOKEN_TILDE)
		{
			if (pTempOffset) delete pTempOffset;
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
			return 0;
		}
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
		Unary* pUnary = new Unary();
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
		pUnary->m_eType = AST::Type::AST_UNARY;
		pUnary->m_pFirstToken = pToken;
		pUnary->m_pExpression = pExpression;
		NumbatLogic::AST* __1929334314 = pExpression;
		pExpression = 0;
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
		pUnary->AddChild(__1929334314);
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::Unary* __2876314212 = pUnary;
#line 27 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
		pUnary = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 27 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
		return __2876314212;
	}

	void Unary::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
		AST::Validate(pValidator, pParent);
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
		if (m_pExpression->m_pValueType == 0)
		{
			InternalString* sTemp = new InternalString("expression did not validate?? ");
			m_pExpression->StringifyType(sTemp);
			pValidator->AddError(sTemp->GetExternalString(), m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
			return;
		}
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
		m_pValueType = m_pExpression->m_pValueType->Clone();
	}

#line 47 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
	void Unary::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/Unary.nll"
	Unary::Unary()
	{
		m_pExpression = 0;
	}

}

