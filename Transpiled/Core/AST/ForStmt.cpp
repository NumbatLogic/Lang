#include "ForStmt.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "VarDecl.hpp"
#include "Scope.hpp"
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
	class VarDecl;
	class Scope;
	class ForStmt;
	class OutputBuilder;
	class Util;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/ForStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ForStmt.nll"
#line 5 "../../../Source/Core/AST/ForStmt.nll"
	ForStmt::ForStmt()
	{
#line 7 "../../../Source/Core/AST/ForStmt.nll"
		m_eType = AST::Type::AST_FOR_STMT;
#line 8 "../../../Source/Core/AST/ForStmt.nll"
		m_bStatement = true;
	}

#line 11 "../../../Source/Core/AST/ForStmt.nll"
	ForStmt* ForStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
#line 13 "../../../Source/Core/AST/ForStmt.nll"
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 15 "../../../Source/Core/AST/ForStmt.nll"
		Token* pForToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_FOR);
#line 16 "../../../Source/Core/AST/ForStmt.nll"
		if (pForToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 17 "../../../Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 18 "../../../Source/Core/AST/ForStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 20 "../../../Source/Core/AST/ForStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
#line 22 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log("expected left paren");
#line 23 "../../../Source/Core/AST/ForStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 24 "../../../Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 26 "../../../Source/Core/AST/ForStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 28 "../../../Source/Core/AST/ForStmt.nll"
		AST* pBeforeStatement = VarDecl::TryCreate(pTokenContainer, pTempOffset, true);
#line 29 "../../../Source/Core/AST/ForStmt.nll"
		if (pBeforeStatement == 0)
		{
#line 31 "../../../Source/Core/AST/ForStmt.nll"
			pBeforeStatement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 32 "../../../Source/Core/AST/ForStmt.nll"
			if (pBeforeStatement == 0)
			{
#line 34 "../../../Source/Core/AST/ForStmt.nll"
				Console::Log("expected before statement");
#line 35 "../../../Source/Core/AST/ForStmt.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 36 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic::Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pBeforeStatement) delete pBeforeStatement;
#line 37 "../../../Source/Core/AST/ForStmt.nll"
				return 0;
			}
		}
#line 41 "../../../Source/Core/AST/ForStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
#line 43 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log("expected semicolon");
#line 44 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 45 "../../../Source/Core/AST/ForStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
#line 46 "../../../Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 48 "../../../Source/Core/AST/ForStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 50 "../../../Source/Core/AST/ForStmt.nll"
		AST* pConditionStatement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 51 "../../../Source/Core/AST/ForStmt.nll"
		if (pConditionStatement == 0)
		{
#line 53 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log("expected condition statement");
#line 54 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 55 "../../../Source/Core/AST/ForStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
			if (pConditionStatement) delete pConditionStatement;
#line 56 "../../../Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 59 "../../../Source/Core/AST/ForStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
#line 61 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log("expected semicolon");
#line 62 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 63 "../../../Source/Core/AST/ForStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
			if (pConditionStatement) delete pConditionStatement;
#line 64 "../../../Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 66 "../../../Source/Core/AST/ForStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 68 "../../../Source/Core/AST/ForStmt.nll"
		AST* pLoopStatement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 77 "../../../Source/Core/AST/ForStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) == 0)
		{
#line 79 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log("expected right paren");
#line 80 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 81 "../../../Source/Core/AST/ForStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
			if (pConditionStatement) delete pConditionStatement;
			if (pLoopStatement) delete pLoopStatement;
#line 82 "../../../Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 84 "../../../Source/Core/AST/ForStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 86 "../../../Source/Core/AST/ForStmt.nll"
		AST* pStatement = Scope::TryCreate(pTokenContainer, pTempOffset, true);
#line 87 "../../../Source/Core/AST/ForStmt.nll"
		if (pStatement == 0)
		{
#line 89 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log("expected statement / scope");
#line 90 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 91 "../../../Source/Core/AST/ForStmt.nll"
			NumbatLogic::Assert::Plz(false);
		}
#line 94 "../../../Source/Core/AST/ForStmt.nll"
		ForStmt* pForStmt = new ForStmt();
#line 95 "../../../Source/Core/AST/ForStmt.nll"
		pForStmt->m_pFirstToken = pForToken;
		NumbatLogic::AST* __2156020446 = pBeforeStatement;
#line 97 "../../../Source/Core/AST/ForStmt.nll"
		pBeforeStatement = 0;
#line 97 "../../../Source/Core/AST/ForStmt.nll"
		pForStmt->AddChild(__2156020446);
		NumbatLogic::AST* __764111395 = pConditionStatement;
#line 98 "../../../Source/Core/AST/ForStmt.nll"
		pConditionStatement = 0;
#line 98 "../../../Source/Core/AST/ForStmt.nll"
		pForStmt->AddChild(__764111395);
#line 99 "../../../Source/Core/AST/ForStmt.nll"
		if (pLoopStatement != 0)
		{
			NumbatLogic::AST* __373112406 = pLoopStatement;
#line 100 "../../../Source/Core/AST/ForStmt.nll"
			pLoopStatement = 0;
#line 100 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt->AddChild(__373112406);
		}
		NumbatLogic::AST* __3036777715 = pStatement;
#line 101 "../../../Source/Core/AST/ForStmt.nll"
		pStatement = 0;
#line 101 "../../../Source/Core/AST/ForStmt.nll"
		pForStmt->AddChild(__3036777715);
#line 103 "../../../Source/Core/AST/ForStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ForStmt* __464585012 = pForStmt;
#line 104 "../../../Source/Core/AST/ForStmt.nll"
		pForStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pBeforeStatement) delete pBeforeStatement;
		if (pConditionStatement) delete pConditionStatement;
		if (pLoopStatement) delete pLoopStatement;
		if (pStatement) delete pStatement;
#line 104 "../../../Source/Core/AST/ForStmt.nll"
		return __464585012;
	}

#line 107 "../../../Source/Core/AST/ForStmt.nll"
	void ForStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 109 "../../../Source/Core/AST/ForStmt.nll"
		AST* pBeforeStatement = m_pFirstChild;
#line 110 "../../../Source/Core/AST/ForStmt.nll"
		AST* pConditionStatement = pBeforeStatement->m_pNextSibling;
#line 111 "../../../Source/Core/AST/ForStmt.nll"
		AST* pLoopStatement = pConditionStatement->m_pNextSibling;
#line 112 "../../../Source/Core/AST/ForStmt.nll"
		AST* pStatement = pLoopStatement->m_pNextSibling;
#line 114 "../../../Source/Core/AST/ForStmt.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 116 "../../../Source/Core/AST/ForStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 117 "../../../Source/Core/AST/ForStmt.nll"
		pOutputBuilder->m_sOut->Append("for (");
#line 118 "../../../Source/Core/AST/ForStmt.nll"
		pBeforeStatement->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 119 "../../../Source/Core/AST/ForStmt.nll"
		pOutputBuilder->m_sOut->Append("; ");
#line 120 "../../../Source/Core/AST/ForStmt.nll"
		pConditionStatement->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 121 "../../../Source/Core/AST/ForStmt.nll"
		pOutputBuilder->m_sOut->Append("; ");
#line 123 "../../../Source/Core/AST/ForStmt.nll"
		if (pStatement != 0)
#line 124 "../../../Source/Core/AST/ForStmt.nll"
			pLoopStatement->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 126 "../../../Source/Core/AST/ForStmt.nll"
		pOutputBuilder->m_sOut->Append(")\n");
#line 128 "../../../Source/Core/AST/ForStmt.nll"
		if (pStatement == 0)
#line 129 "../../../Source/Core/AST/ForStmt.nll"
			pStatement = pLoopStatement;
#line 131 "../../../Source/Core/AST/ForStmt.nll"
		pStatement->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
	}

}

