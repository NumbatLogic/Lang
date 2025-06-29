#include "BreakStmt.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST.hpp"
#include "../Validator.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class BreakStmt;
}
namespace NumbatLogic
{
	BreakStmt::BreakStmt()
	{
		m_bStatement = true;
	}

	BreakStmt* BreakStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pBreakToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_BREAK);
		if (pBreakToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			Console::Log("expected semicolon");
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		BreakStmt* pBreakStmt = new BreakStmt();
		pBreakStmt->m_eType = AST::Type::AST_BREAK_STMT;
		pBreakStmt->m_pFirstToken = pBreakToken;
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::BreakStmt* __136854138 = pBreakStmt;
		pBreakStmt = 0;
		if (pTempOffset) delete pTempOffset;
		return __136854138;
	}

	void BreakStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		pValidator->InjectCleanup(this);
	}

	void BreakStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		Util::Pad(nDepth, sOut);
		sOut->Append("break;\n");
	}

}

