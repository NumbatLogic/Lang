#include "BreakStmt.hpp"
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
	class BreakStmt;
	class Validator;
	class OutputBuilder;
	class Util;
	class InternalString;
}
#line 1 "../../../Source/Core/AST/BreakStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/BreakStmt.nll"
#line 6 "../../../Source/Core/AST/BreakStmt.nll"
	BreakStmt::BreakStmt()
	{
#line 8 "../../../Source/Core/AST/BreakStmt.nll"
		m_bStatement = true;
	}

#line 11 "../../../Source/Core/AST/BreakStmt.nll"
	BreakStmt* BreakStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pBreakToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_BREAK);
#line 16 "../../../Source/Core/AST/BreakStmt.nll"
		if (pBreakToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 17 "../../../Source/Core/AST/BreakStmt.nll"
			return 0;
		}
#line 18 "../../../Source/Core/AST/BreakStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 20 "../../../Source/Core/AST/BreakStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
#line 22 "../../../Source/Core/AST/BreakStmt.nll"
			Console::Log("expected semicolon");
#line 23 "../../../Source/Core/AST/BreakStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 24 "../../../Source/Core/AST/BreakStmt.nll"
			return 0;
		}
#line 26 "../../../Source/Core/AST/BreakStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		BreakStmt* pBreakStmt = new BreakStmt();
#line 30 "../../../Source/Core/AST/BreakStmt.nll"
		pBreakStmt->m_eType = AST::Type::AST_BREAK_STMT;
#line 31 "../../../Source/Core/AST/BreakStmt.nll"
		pBreakStmt->m_pFirstToken = pBreakToken;
#line 33 "../../../Source/Core/AST/BreakStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::BreakStmt* __3206362871 = pBreakStmt;
#line 34 "../../../Source/Core/AST/BreakStmt.nll"
		pBreakStmt = 0;
		if (pTempOffset) delete pTempOffset;
#line 34 "../../../Source/Core/AST/BreakStmt.nll"
		return __3206362871;
	}

#line 37 "../../../Source/Core/AST/BreakStmt.nll"
	void BreakStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 39 "../../../Source/Core/AST/BreakStmt.nll"
		AST::Validate(pValidator, pParent);
#line 40 "../../../Source/Core/AST/BreakStmt.nll"
		pValidator->InjectCleanup(this);
	}

#line 43 "../../../Source/Core/AST/BreakStmt.nll"
	void BreakStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 45 "../../../Source/Core/AST/BreakStmt.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 47 "../../../Source/Core/AST/BreakStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 48 "../../../Source/Core/AST/BreakStmt.nll"
		pOutputBuilder->m_sOut->Append("break;\n");
	}

}

