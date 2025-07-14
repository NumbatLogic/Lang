#include "ContinueStmt.hpp"
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
	class ContinueStmt;
	class OffsetDatum;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Token;
	class Console;
	class Assert;
	class ContinueStmt;
	class AST;
	class Validator;
	class Util;
	class InternalString;
}
namespace NumbatLogic
{
	ContinueStmt::ContinueStmt()
	{
		m_bStatement = true;
	}

	ContinueStmt* ContinueStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pBreakToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CONTINUE);
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
		ContinueStmt* pContinueStmt = new ContinueStmt();
		pContinueStmt->m_eType = AST::Type::AST_CONTINUE_STMT;
		pContinueStmt->m_pFirstToken = pBreakToken;
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ContinueStmt* __3322157729 = pContinueStmt;
		pContinueStmt = 0;
		if (pTempOffset) delete pTempOffset;
		return __3322157729;
	}

	void ContinueStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		pValidator->InjectCleanup(this);
	}

	void ContinueStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		Util::Pad(nDepth, sOut);
		sOut->Append("continue;\n");
	}

}

