#include "ReturnStmt.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../Validator.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class ReturnStmt;
	class Validator;
	class OutputBuilder;
	class Util;
	class InternalString;
}
#line 1 "../../../Source/Core/AST/ReturnStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/ReturnStmt.nll"
#line 8 "../../../Source/Core/AST/ReturnStmt.nll"
	ReturnStmt::ReturnStmt()
	{
		m_pExpression = 0;
#line 10 "../../../Source/Core/AST/ReturnStmt.nll"
		m_eType = AST::Type::AST_RETURN_STMT;
#line 11 "../../../Source/Core/AST/ReturnStmt.nll"
		m_bStatement = true;
	}

#line 14 "../../../Source/Core/AST/ReturnStmt.nll"
	ReturnStmt* ReturnStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pReturnToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_RETURN);
#line 19 "../../../Source/Core/AST/ReturnStmt.nll"
		if (pReturnToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 20 "../../../Source/Core/AST/ReturnStmt.nll"
			return 0;
		}
#line 21 "../../../Source/Core/AST/ReturnStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 25 "../../../Source/Core/AST/ReturnStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 26 "../../../Source/Core/AST/ReturnStmt.nll"
			return 0;
		}
#line 27 "../../../Source/Core/AST/ReturnStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ReturnStmt* pReturnStmt = new ReturnStmt();
#line 31 "../../../Source/Core/AST/ReturnStmt.nll"
		pReturnStmt->m_pFirstToken = pReturnToken;
#line 32 "../../../Source/Core/AST/ReturnStmt.nll"
		pReturnStmt->m_pExpression = pExpression;
#line 34 "../../../Source/Core/AST/ReturnStmt.nll"
		if (pExpression != 0)
		{
			NumbatLogic::AST* __1929399913 = pExpression;
#line 35 "../../../Source/Core/AST/ReturnStmt.nll"
			pExpression = 0;
#line 35 "../../../Source/Core/AST/ReturnStmt.nll"
			pReturnStmt->AddChild(__1929399913);
		}
#line 37 "../../../Source/Core/AST/ReturnStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ReturnStmt* __2739522412 = pReturnStmt;
#line 38 "../../../Source/Core/AST/ReturnStmt.nll"
		pReturnStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 38 "../../../Source/Core/AST/ReturnStmt.nll"
		return __2739522412;
	}

#line 41 "../../../Source/Core/AST/ReturnStmt.nll"
	void ReturnStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 43 "../../../Source/Core/AST/ReturnStmt.nll"
		AST::Validate(pValidator, pParent);
#line 44 "../../../Source/Core/AST/ReturnStmt.nll"
		pValidator->InjectCleanup(this);
	}

#line 47 "../../../Source/Core/AST/ReturnStmt.nll"
	void ReturnStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 49 "../../../Source/Core/AST/ReturnStmt.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 50 "../../../Source/Core/AST/ReturnStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 52 "../../../Source/Core/AST/ReturnStmt.nll"
		pOutputBuilder->m_sOut->AppendString("return");
#line 53 "../../../Source/Core/AST/ReturnStmt.nll"
		if (m_pExpression != 0)
		{
#line 55 "../../../Source/Core/AST/ReturnStmt.nll"
			pOutputBuilder->m_sOut->AppendChar(' ');
#line 56 "../../../Source/Core/AST/ReturnStmt.nll"
			m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
#line 58 "../../../Source/Core/AST/ReturnStmt.nll"
		pOutputBuilder->m_sOut->AppendString(";\n");
	}

}

