#include "SwitchStmt.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "Scope.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class SwitchStmt;
}
namespace NumbatLogic
{
	SwitchStmt::SwitchStmt()
	{
		m_pExpression = 0;
		m_pExpressionVector = 0;
		m_pStatementVector = 0;
		m_pDefaultStatement = 0;
		m_eType = AST::Type::AST_SWITCH_STMT;
		m_bStatement = true;
		m_pExpressionVector = new Vector<AST*>();
		m_pStatementVector = new Vector<AST*>();
		m_pDefaultStatement = 0;
	}

	SwitchStmt* SwitchStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pSwitchToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_SWITCH);
		if (pSwitchToken == 0)
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
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pExpression == 0)
		{
			Console::Log("expected expression");
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
			return 0;
		}
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) == 0)
		{
			Console::Log("expected right paren");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT) == 0)
		{
			Console::Log("expected opening curly brace");
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		SwitchStmt* pSwitchStmt = new SwitchStmt();
		pSwitchStmt->m_pFirstToken = pSwitchToken;
		pSwitchStmt->m_pExpression = pExpression;
		NumbatLogic::AST* __75417520 = pExpression;
		pExpression = 0;
		pSwitchStmt->AddChild(__75417520);
		while (true)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
			if (pSwitchStmt->m_pDefaultStatement != 0)
			{
				Console::Log("expected default to be last thing in switch statement");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pSwitchStmt) delete pSwitchStmt;
				return 0;
			}
			Token* pCaseToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CASE);
			Token* pDefaultToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DEFAULT);
			if (pCaseToken == 0 && pDefaultToken == 0)
			{
				Console::Log("expected case or default");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pSwitchStmt) delete pSwitchStmt;
				return 0;
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			if (pDefaultToken != 0)
			{
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COLON) == 0)
				{
					Console::Log("expected colon A");
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
					NumbatLogic::Assert::Plz(false);
					if (pTempOffset) delete pTempOffset;
					if (pExpression) delete pExpression;
					if (pSwitchStmt) delete pSwitchStmt;
					return 0;
				}
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				AST* pDefaultStatement = AST::CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
				if (pDefaultStatement == 0)
				{
					Console::Log("expected case statement");
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
					NumbatLogic::Assert::Plz(false);
					if (pDefaultStatement) delete pDefaultStatement;
					if (pTempOffset) delete pTempOffset;
					if (pExpression) delete pExpression;
					if (pSwitchStmt) delete pSwitchStmt;
					return 0;
				}
				AST* pScopedDefaultStatement = 0;
				if (pDefaultStatement->m_eType == AST::Type::AST_SCOPE)
				{
					NumbatLogic::AST* __1943075521 = pDefaultStatement;
					pDefaultStatement = 0;
					pScopedDefaultStatement = __1943075521;
				}
				else
				{
					pScopedDefaultStatement = new Scope();
					NumbatLogic::AST* __1859158196 = pDefaultStatement;
					pDefaultStatement = 0;
					pScopedDefaultStatement->AddChild(__1859158196);
				}
				pSwitchStmt->m_pDefaultStatement = pScopedDefaultStatement;
				NumbatLogic::AST* __4123816369 = pScopedDefaultStatement;
				pScopedDefaultStatement = 0;
				pSwitchStmt->AddChild(__4123816369);
				if (pDefaultStatement) delete pDefaultStatement;
				if (pScopedDefaultStatement) delete pScopedDefaultStatement;
				continue;
			}
			AST* pCaseExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pCaseExpression == 0)
			{
				Console::Log("expected case expression");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pCaseExpression) delete pCaseExpression;
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pSwitchStmt) delete pSwitchStmt;
				return 0;
			}
			pSwitchStmt->m_pExpressionVector->PushBack(pCaseExpression);
			NumbatLogic::AST* __1609920147 = pCaseExpression;
			pCaseExpression = 0;
			pSwitchStmt->AddChild(__1609920147);
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COLON) == 0)
			{
				Console::Log("expected colon B");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pCaseExpression) delete pCaseExpression;
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pSwitchStmt) delete pSwitchStmt;
				return 0;
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CASE) != 0)
			{
				pSwitchStmt->m_pStatementVector->PushBack(0);
				if (pCaseExpression) delete pCaseExpression;
				continue;
			}
			AST* pCaseStatement = AST::CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
			if (pCaseStatement == 0)
			{
				Console::Log("expected case statement");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pCaseExpression) delete pCaseExpression;
				if (pCaseStatement) delete pCaseStatement;
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pSwitchStmt) delete pSwitchStmt;
				return 0;
			}
			AST* pScopedCaseStatement = 0;
			if (pCaseStatement->m_eType == AST::Type::AST_SCOPE)
			{
				NumbatLogic::AST* __3494567234 = pCaseStatement;
				pCaseStatement = 0;
				pScopedCaseStatement = __3494567234;
			}
			else
			{
				pScopedCaseStatement = new Scope();
				NumbatLogic::AST* __1732965839 = pCaseStatement;
				pCaseStatement = 0;
				pScopedCaseStatement->AddChild(__1732965839);
			}
			pSwitchStmt->m_pStatementVector->PushBack(pScopedCaseStatement);
			NumbatLogic::AST* __1861627875 = pScopedCaseStatement;
			pScopedCaseStatement = 0;
			pSwitchStmt->AddChild(__1861627875);
			if (pCaseExpression) delete pCaseExpression;
			if (pCaseStatement) delete pCaseStatement;
			if (pScopedCaseStatement) delete pScopedCaseStatement;
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::SwitchStmt* __3401844597 = pSwitchStmt;
		pSwitchStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
		return __3401844597;
	}

	void SwitchStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		Util::Pad(nDepth, sOut);
		sOut->Append("switch (");
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->Append(")\n");
		Util::Pad(nDepth, sOut);
		sOut->Append("{\n");
		nDepth++;
		for (int i = 0; i < m_pExpressionVector->GetSize(); i++)
		{
			AST* pCaseExpression = m_pExpressionVector->Get(i);
			AST* pCaseStatement = m_pStatementVector->Get(i);
			Util::Pad(nDepth, sOut);
			sOut->Append("case ");
			pCaseExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut->Append(":\n");
			if (pCaseStatement != 0)
			{
				pCaseStatement->Stringify(eLanguage, eOutputFile, nDepth, sOut);
				sOut->Append("\n");
			}
		}
		if (m_pDefaultStatement != 0)
		{
			Util::Pad(nDepth, sOut);
			sOut->Append("default:\n");
			m_pDefaultStatement->Stringify(eLanguage, eOutputFile, nDepth, sOut);
			sOut->Append("\n");
		}
		nDepth--;
		Util::Pad(nDepth, sOut);
		sOut->AppendString("}\n");
	}

	SwitchStmt::~SwitchStmt()
	{
		if (m_pExpressionVector) delete m_pExpressionVector;
		if (m_pStatementVector) delete m_pStatementVector;
	}

}

