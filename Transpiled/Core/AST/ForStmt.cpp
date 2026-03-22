#include "ForStmt.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "VarDecl.hpp"
#include "Scope.hpp"
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
	class VarDecl;
	class Scope;
	class ForStmt;
	class OutputBuilder;
	class Util;
	class InternalString;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
	ForStmt::ForStmt()
	{
		m_eType = AST::Type::AST_FOR_STMT;
		m_bStatement = true;
	}

	ForStmt* ForStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 15 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		Token* pForToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_FOR);
		if (pForToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
			Console::Log("expected left paren");
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 28 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
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
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
				return 0;
			}
		}
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			Console::Log("expected semicolon");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 50 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		AST* pConditionStatement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pConditionStatement == 0)
		{
			Console::Log("expected condition statement");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
			if (pConditionStatement) delete pConditionStatement;
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 59 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			Console::Log("expected semicolon");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
			if (pConditionStatement) delete pConditionStatement;
#line 64 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 68 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		AST* pLoopStatement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 77 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) == 0)
		{
			Console::Log("expected right paren");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
			if (pConditionStatement) delete pConditionStatement;
			if (pLoopStatement) delete pLoopStatement;
#line 82 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 86 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		AST* pStatement = Scope::TryCreate(pTokenContainer, pTempOffset, true);
		if (pStatement == 0)
		{
			Console::Log("expected statement / scope");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
		}
#line 94 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		ForStmt* pForStmt = new ForStmt();
		pForStmt->m_pFirstToken = pForToken;
		NumbatLogic::AST* __2156020446 = pBeforeStatement;
		pBeforeStatement = 0;
#line 97 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		pForStmt->AddChild(__2156020446);
		NumbatLogic::AST* __764111395 = pConditionStatement;
#line 98 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		pConditionStatement = 0;
#line 98 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		pForStmt->AddChild(__764111395);
		if (pLoopStatement != 0)
		{
			NumbatLogic::AST* __373112406 = pLoopStatement;
#line 100 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
			pLoopStatement = 0;
#line 100 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
			pForStmt->AddChild(__373112406);
		}
		NumbatLogic::AST* __3036777715 = pStatement;
#line 101 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		pStatement = 0;
#line 101 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		pForStmt->AddChild(__3036777715);
#line 103 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ForStmt* __464585012 = pForStmt;
#line 104 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		pForStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pBeforeStatement) delete pBeforeStatement;
		if (pConditionStatement) delete pConditionStatement;
		if (pLoopStatement) delete pLoopStatement;
		if (pStatement) delete pStatement;
#line 104 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		return __464585012;
	}

	void ForStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		AST* pBeforeStatement = m_pFirstChild;
		AST* pConditionStatement = pBeforeStatement->m_pNextSibling;
		AST* pLoopStatement = pConditionStatement->m_pNextSibling;
		AST* pStatement = pLoopStatement->m_pNextSibling;
#line 114 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 116 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("for (");
		pBeforeStatement->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		pOutputBuilder->m_sOut->Append("; ");
		pConditionStatement->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		pOutputBuilder->m_sOut->Append("; ");
#line 123 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		if (pStatement != 0)
			pLoopStatement->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 126 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		pOutputBuilder->m_sOut->Append(")\n");
#line 128 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		if (pStatement == 0)
			pStatement = pLoopStatement;
#line 131 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		pStatement->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
	}

}

