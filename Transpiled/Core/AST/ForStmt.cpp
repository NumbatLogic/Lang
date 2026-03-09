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
#line 1 "../../../Source/Core/AST/ForStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/ForStmt.nll"
#line 6 "../../../Source/Core/AST/ForStmt.nll"
	ForStmt::ForStmt()
	{
#line 8 "../../../Source/Core/AST/ForStmt.nll"
		m_eType = AST::Type::AST_FOR_STMT;
#line 9 "../../../Source/Core/AST/ForStmt.nll"
		m_bStatement = true;
	}

#line 12 "../../../Source/Core/AST/ForStmt.nll"
	ForStmt* ForStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pForToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_FOR);
#line 17 "../../../Source/Core/AST/ForStmt.nll"
		if (pForToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 18 "../../../Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 19 "../../../Source/Core/AST/ForStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 21 "../../../Source/Core/AST/ForStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
#line 23 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log("expected left paren");
#line 24 "../../../Source/Core/AST/ForStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 25 "../../../Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 27 "../../../Source/Core/AST/ForStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pBeforeStatement = VarDecl::TryCreate(pTokenContainer, pTempOffset, true);
#line 30 "../../../Source/Core/AST/ForStmt.nll"
		if (pBeforeStatement == 0)
		{
#line 32 "../../../Source/Core/AST/ForStmt.nll"
			pBeforeStatement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 33 "../../../Source/Core/AST/ForStmt.nll"
			if (pBeforeStatement == 0)
			{
#line 35 "../../../Source/Core/AST/ForStmt.nll"
				Console::Log("expected before statement");
#line 36 "../../../Source/Core/AST/ForStmt.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 37 "../../../Source/Core/AST/ForStmt.nll"
				NumbatLogic::Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pBeforeStatement) delete pBeforeStatement;
#line 38 "../../../Source/Core/AST/ForStmt.nll"
				return 0;
			}
		}
#line 42 "../../../Source/Core/AST/ForStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
#line 44 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log("expected semicolon");
#line 45 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 46 "../../../Source/Core/AST/ForStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
#line 47 "../../../Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 49 "../../../Source/Core/AST/ForStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pConditionStatement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 52 "../../../Source/Core/AST/ForStmt.nll"
		if (pConditionStatement == 0)
		{
#line 54 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log("expected condition statement");
#line 55 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 56 "../../../Source/Core/AST/ForStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
			if (pConditionStatement) delete pConditionStatement;
#line 57 "../../../Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 60 "../../../Source/Core/AST/ForStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
#line 62 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log("expected semicolon");
#line 63 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 64 "../../../Source/Core/AST/ForStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
			if (pConditionStatement) delete pConditionStatement;
#line 65 "../../../Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 67 "../../../Source/Core/AST/ForStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pLoopStatement = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 78 "../../../Source/Core/AST/ForStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) == 0)
		{
#line 80 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log("expected right paren");
#line 81 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 82 "../../../Source/Core/AST/ForStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pBeforeStatement) delete pBeforeStatement;
			if (pConditionStatement) delete pConditionStatement;
			if (pLoopStatement) delete pLoopStatement;
#line 83 "../../../Source/Core/AST/ForStmt.nll"
			return 0;
		}
#line 85 "../../../Source/Core/AST/ForStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pStatement = Scope::TryCreate(pTokenContainer, pTempOffset, true);
#line 88 "../../../Source/Core/AST/ForStmt.nll"
		if (pStatement == 0)
		{
#line 90 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log("expected statement / scope");
#line 91 "../../../Source/Core/AST/ForStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 92 "../../../Source/Core/AST/ForStmt.nll"
			NumbatLogic::Assert::Plz(false);
		}
		ForStmt* pForStmt = new ForStmt();
#line 96 "../../../Source/Core/AST/ForStmt.nll"
		pForStmt->m_pFirstToken = pForToken;
		NumbatLogic::AST* __2156020446 = pBeforeStatement;
#line 98 "../../../Source/Core/AST/ForStmt.nll"
		pBeforeStatement = 0;
#line 98 "../../../Source/Core/AST/ForStmt.nll"
		pForStmt->AddChild(__2156020446);
		NumbatLogic::AST* __764111395 = pConditionStatement;
#line 99 "../../../Source/Core/AST/ForStmt.nll"
		pConditionStatement = 0;
#line 99 "../../../Source/Core/AST/ForStmt.nll"
		pForStmt->AddChild(__764111395);
#line 100 "../../../Source/Core/AST/ForStmt.nll"
		if (pLoopStatement != 0)
		{
			NumbatLogic::AST* __373112406 = pLoopStatement;
#line 101 "../../../Source/Core/AST/ForStmt.nll"
			pLoopStatement = 0;
#line 101 "../../../Source/Core/AST/ForStmt.nll"
			pForStmt->AddChild(__373112406);
		}
		NumbatLogic::AST* __3036777715 = pStatement;
#line 102 "../../../Source/Core/AST/ForStmt.nll"
		pStatement = 0;
#line 102 "../../../Source/Core/AST/ForStmt.nll"
		pForStmt->AddChild(__3036777715);
#line 104 "../../../Source/Core/AST/ForStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ForStmt* __464585012 = pForStmt;
#line 105 "../../../Source/Core/AST/ForStmt.nll"
		pForStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pBeforeStatement) delete pBeforeStatement;
		if (pConditionStatement) delete pConditionStatement;
		if (pLoopStatement) delete pLoopStatement;
		if (pStatement) delete pStatement;
#line 105 "../../../Source/Core/AST/ForStmt.nll"
		return __464585012;
	}

#line 108 "../../../Source/Core/AST/ForStmt.nll"
	void ForStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		AST* pBeforeStatement = m_pFirstChild;
		AST* pConditionStatement = pBeforeStatement->m_pNextSibling;
		AST* pLoopStatement = pConditionStatement->m_pNextSibling;
		AST* pStatement = pLoopStatement->m_pNextSibling;
#line 115 "../../../Source/Core/AST/ForStmt.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 117 "../../../Source/Core/AST/ForStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 118 "../../../Source/Core/AST/ForStmt.nll"
		pOutputBuilder->m_sOut->Append("for (");
#line 119 "../../../Source/Core/AST/ForStmt.nll"
		pBeforeStatement->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 120 "../../../Source/Core/AST/ForStmt.nll"
		pOutputBuilder->m_sOut->Append("; ");
#line 121 "../../../Source/Core/AST/ForStmt.nll"
		pConditionStatement->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 122 "../../../Source/Core/AST/ForStmt.nll"
		pOutputBuilder->m_sOut->Append("; ");
#line 124 "../../../Source/Core/AST/ForStmt.nll"
		if (pStatement != 0)
#line 125 "../../../Source/Core/AST/ForStmt.nll"
			pLoopStatement->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 127 "../../../Source/Core/AST/ForStmt.nll"
		pOutputBuilder->m_sOut->Append(")\n");
#line 129 "../../../Source/Core/AST/ForStmt.nll"
		if (pStatement == 0)
#line 130 "../../../Source/Core/AST/ForStmt.nll"
			pStatement = pLoopStatement;
#line 132 "../../../Source/Core/AST/ForStmt.nll"
		pStatement->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
	}

}

