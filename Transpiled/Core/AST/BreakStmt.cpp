#include "BreakStmt.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "AST.hpp"
#include "../Validator.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Console;
	class Assert;
	class BreakStmt;
	class Validator;
	class OutputBuilder;
	class Util;
	class InternalString;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
	BreakStmt::BreakStmt()
	{
		m_bStatement = true;
	}

	BreakStmt* BreakStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
		Token* pBreakToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_BREAK);
		if (pBreakToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
			return 0;
		}
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			Console::Log("expected semicolon");
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 27 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
		BreakStmt* pBreakStmt = new BreakStmt();
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
		pBreakStmt->m_eType = AST::Type::AST_BREAK_STMT;
		pBreakStmt->m_pFirstToken = pBreakToken;
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::BreakStmt* __3206362871 = pBreakStmt;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
		pBreakStmt = 0;
		if (pTempOffset) delete pTempOffset;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
		return __3206362871;
	}

	void BreakStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		pValidator->InjectCleanup(this);
	}

	void BreakStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/BreakStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("break;\n");
	}

}

