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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
	ReturnStmt::ReturnStmt()
	{
		m_pExpression = 0;
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		m_eType = AST::Type::AST_RETURN_STMT;
		m_bStatement = true;
	}

	ReturnStmt* ReturnStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		Token* pReturnToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_RETURN);
		if (pReturnToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			return 0;
		}
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 25 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			return 0;
		}
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 28 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		ReturnStmt* pReturnStmt = new ReturnStmt();
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		pReturnStmt->m_pFirstToken = pReturnToken;
		pReturnStmt->m_pExpression = pExpression;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		if (pExpression != 0)
		{
			NumbatLogic::AST* __1929399913 = pExpression;
#line 34 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			pExpression = 0;
#line 34 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
			pReturnStmt->AddChild(__1929399913);
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ReturnStmt* __2739522412 = pReturnStmt;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		pReturnStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		return __2739522412;
	}

	void ReturnStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		pValidator->InjectCleanup(this);
	}

	void ReturnStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		pOutputBuilder->m_sOut->AppendString("return");
		if (m_pExpression != 0)
		{
			pOutputBuilder->m_sOut->AppendChar(' ');
			m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
		pOutputBuilder->m_sOut->AppendString(";\n");
	}

}

