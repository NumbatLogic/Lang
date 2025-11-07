#include "ForStmt.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "VarDecl.hpp"
#include "Scope.hpp"
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
	class VarDecl;
	class Scope;
	class ForStmt;
	class Util;
	class InternalString;
}
namespace NumbatLogic
{
	ForStmt::ForStmt()
	{
		m_eType = AST::Type::AST_FOR_STMT;
		m_bStatement = true;
	}

	ForStmt* ForStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pForToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_FOR);
		if (pForToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
			Console::Log("expected left paren");
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pBeforeStatement = VarDecl::TryCreate(pTokenContainer, pTempOffset, true);
		if (pBeforeStatement == 0)
		{
			pBeforeStatement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pBeforeStatement == 0)
			{
				Console::Log("expected before statement");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pBeforeStatement) delete pBeforeStatement;
				return 0;
			}
		}
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			Console::Log("expected semicolon");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pConditionStatement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pConditionStatement == 0)
		{
			Console::Log("expected condition statement");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
			if (pConditionStatement) delete pConditionStatement;
			return 0;
		}
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			Console::Log("expected semicolon");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
			if (pConditionStatement) delete pConditionStatement;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pLoopStatement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) == 0)
		{
			Console::Log("expected right paren");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
			if (pConditionStatement) delete pConditionStatement;
			if (pLoopStatement) delete pLoopStatement;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pStatement = Scope::TryCreate(pTokenContainer, pTempOffset, true);
		if (pStatement == 0)
		{
			Console::Log("expected statement / scope");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
		}
		ForStmt* pForStmt = new ForStmt();
		pForStmt->m_pFirstToken = pForToken;
		NumbatLogic::AST* __3480122444 = pBeforeStatement;
		pBeforeStatement = 0;
		pForStmt->AddChild(__3480122444);
		NumbatLogic::AST* __1349416048 = pConditionStatement;
		pConditionStatement = 0;
		pForStmt->AddChild(__1349416048);
		if (pLoopStatement != 0)
		{
			NumbatLogic::AST* __3115963264 = pLoopStatement;
			pLoopStatement = 0;
			pForStmt->AddChild(__3115963264);
		}
		NumbatLogic::AST* __96064388 = pStatement;
		pStatement = 0;
		pForStmt->AddChild(__96064388);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ForStmt* __1367101328 = pForStmt;
		pForStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pBeforeStatement) delete pBeforeStatement;
		if (pConditionStatement) delete pConditionStatement;
		if (pLoopStatement) delete pLoopStatement;
		if (pStatement) delete pStatement;
		return __1367101328;
	}

	void ForStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		AST* pBeforeStatement = m_pFirstChild;
		AST* pConditionStatement = pBeforeStatement->m_pNextSibling;
		AST* pLoopStatement = pConditionStatement->m_pNextSibling;
		AST* pStatement = pLoopStatement->m_pNextSibling;
		Util::Pad(nDepth, sOut);
		sOut->Append("for (");
		pBeforeStatement->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->Append("; ");
		pConditionStatement->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->Append("; ");
		if (pStatement != 0)
			pLoopStatement->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->Append(")\n");
		if (pStatement == 0)
			pStatement = pLoopStatement;
		pStatement->Stringify(eLanguage, eOutputFile, nDepth, sOut);
	}

}

