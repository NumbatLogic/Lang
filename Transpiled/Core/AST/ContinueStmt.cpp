#include "ContinueStmt.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST.hpp"
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
	class Console;
	class Assert;
	class ContinueStmt;
	class Validator;
	class OutputBuilder;
	class Util;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/ContinueStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ContinueStmt.nll"
#line 5 "../../../Source/Core/AST/ContinueStmt.nll"
	ContinueStmt::ContinueStmt()
	{
		m_bStatement = true;
	}

	ContinueStmt* ContinueStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 14 "../../../Source/Core/AST/ContinueStmt.nll"
		Token* pBreakToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CONTINUE);
		if (pBreakToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 16 "../../../Source/Core/AST/ContinueStmt.nll"
			return 0;
		}
#line 17 "../../../Source/Core/AST/ContinueStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 19 "../../../Source/Core/AST/ContinueStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			Console::Log("expected semicolon");
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 23 "../../../Source/Core/AST/ContinueStmt.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 27 "../../../Source/Core/AST/ContinueStmt.nll"
		ContinueStmt* pContinueStmt = new ContinueStmt();
#line 29 "../../../Source/Core/AST/ContinueStmt.nll"
		pContinueStmt->m_eType = AST::Type::AST_CONTINUE_STMT;
		pContinueStmt->m_pFirstToken = pBreakToken;
#line 32 "../../../Source/Core/AST/ContinueStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ContinueStmt* __2497879999 = pContinueStmt;
#line 33 "../../../Source/Core/AST/ContinueStmt.nll"
		pContinueStmt = 0;
		if (pTempOffset) delete pTempOffset;
#line 33 "../../../Source/Core/AST/ContinueStmt.nll"
		return __2497879999;
	}

	void ContinueStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		pValidator->InjectCleanup(this);
	}

	void ContinueStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("continue;\n");
	}

}

