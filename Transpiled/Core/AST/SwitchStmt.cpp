#include "SwitchStmt.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "Scope.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	template <class T>
	class Vector;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Console;
	class Assert;
	class SwitchStmt;
	class Scope;
	class OutputBuilder;
	class Util;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/SwitchStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/SwitchStmt.nll"
#line 10 "../../../Source/Core/AST/SwitchStmt.nll"
	SwitchStmt::SwitchStmt()
	{
		m_pExpression = 0;
		m_pExpressionVector = 0;
		m_pStatementVector = 0;
		m_pDefaultStatement = 0;
#line 12 "../../../Source/Core/AST/SwitchStmt.nll"
		m_eType = AST::Type::AST_SWITCH_STMT;
#line 13 "../../../Source/Core/AST/SwitchStmt.nll"
		m_bStatement = true;
#line 14 "../../../Source/Core/AST/SwitchStmt.nll"
		m_pExpressionVector = new Vector<AST*>();
#line 15 "../../../Source/Core/AST/SwitchStmt.nll"
		m_pStatementVector = new Vector<AST*>();
#line 16 "../../../Source/Core/AST/SwitchStmt.nll"
		m_pDefaultStatement = 0;
	}

#line 19 "../../../Source/Core/AST/SwitchStmt.nll"
	SwitchStmt* SwitchStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
#line 21 "../../../Source/Core/AST/SwitchStmt.nll"
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 23 "../../../Source/Core/AST/SwitchStmt.nll"
		Token* pSwitchToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_SWITCH);
#line 24 "../../../Source/Core/AST/SwitchStmt.nll"
		if (pSwitchToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 25 "../../../Source/Core/AST/SwitchStmt.nll"
			return 0;
		}
#line 26 "../../../Source/Core/AST/SwitchStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 28 "../../../Source/Core/AST/SwitchStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
#line 30 "../../../Source/Core/AST/SwitchStmt.nll"
			Console::Log("expected left paren");
#line 31 "../../../Source/Core/AST/SwitchStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 32 "../../../Source/Core/AST/SwitchStmt.nll"
			return 0;
		}
#line 34 "../../../Source/Core/AST/SwitchStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 36 "../../../Source/Core/AST/SwitchStmt.nll"
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 37 "../../../Source/Core/AST/SwitchStmt.nll"
		if (pExpression == 0)
		{
#line 39 "../../../Source/Core/AST/SwitchStmt.nll"
			Console::Log("expected expression");
#line 40 "../../../Source/Core/AST/SwitchStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 41 "../../../Source/Core/AST/SwitchStmt.nll"
			return 0;
		}
#line 44 "../../../Source/Core/AST/SwitchStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) == 0)
		{
#line 46 "../../../Source/Core/AST/SwitchStmt.nll"
			Console::Log("expected right paren");
#line 47 "../../../Source/Core/AST/SwitchStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 48 "../../../Source/Core/AST/SwitchStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 49 "../../../Source/Core/AST/SwitchStmt.nll"
			return 0;
		}
#line 51 "../../../Source/Core/AST/SwitchStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 53 "../../../Source/Core/AST/SwitchStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT) == 0)
		{
#line 55 "../../../Source/Core/AST/SwitchStmt.nll"
			Console::Log("expected opening curly brace");
#line 56 "../../../Source/Core/AST/SwitchStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 57 "../../../Source/Core/AST/SwitchStmt.nll"
			return 0;
		}
#line 59 "../../../Source/Core/AST/SwitchStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 62 "../../../Source/Core/AST/SwitchStmt.nll"
		SwitchStmt* pSwitchStmt = new SwitchStmt();
#line 63 "../../../Source/Core/AST/SwitchStmt.nll"
		pSwitchStmt->m_pFirstToken = pSwitchToken;
#line 64 "../../../Source/Core/AST/SwitchStmt.nll"
		pSwitchStmt->m_pExpression = pExpression;
		NumbatLogic::AST* __1929596711 = pExpression;
#line 65 "../../../Source/Core/AST/SwitchStmt.nll"
		pExpression = 0;
#line 65 "../../../Source/Core/AST/SwitchStmt.nll"
		pSwitchStmt->AddChild(__1929596711);
#line 67 "../../../Source/Core/AST/SwitchStmt.nll"
		while (true)
		{
#line 69 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
#line 71 "../../../Source/Core/AST/SwitchStmt.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 72 "../../../Source/Core/AST/SwitchStmt.nll"
				break;
			}
#line 75 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pSwitchStmt->m_pDefaultStatement != 0)
			{
#line 77 "../../../Source/Core/AST/SwitchStmt.nll"
				Console::Log("expected default to be last thing in switch statement");
#line 78 "../../../Source/Core/AST/SwitchStmt.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 79 "../../../Source/Core/AST/SwitchStmt.nll"
				NumbatLogic::Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pSwitchStmt) delete pSwitchStmt;
#line 80 "../../../Source/Core/AST/SwitchStmt.nll"
				return 0;
			}
#line 83 "../../../Source/Core/AST/SwitchStmt.nll"
			Token* pCaseToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CASE);
#line 84 "../../../Source/Core/AST/SwitchStmt.nll"
			Token* pDefaultToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DEFAULT);
#line 85 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pCaseToken == 0 && pDefaultToken == 0)
			{
#line 87 "../../../Source/Core/AST/SwitchStmt.nll"
				Console::Log("expected case or default");
#line 88 "../../../Source/Core/AST/SwitchStmt.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 89 "../../../Source/Core/AST/SwitchStmt.nll"
				NumbatLogic::Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pSwitchStmt) delete pSwitchStmt;
#line 90 "../../../Source/Core/AST/SwitchStmt.nll"
				return 0;
			}
#line 92 "../../../Source/Core/AST/SwitchStmt.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 94 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pDefaultToken != 0)
			{
#line 96 "../../../Source/Core/AST/SwitchStmt.nll"
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COLON) == 0)
				{
#line 98 "../../../Source/Core/AST/SwitchStmt.nll"
					Console::Log("expected colon A");
#line 99 "../../../Source/Core/AST/SwitchStmt.nll"
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 100 "../../../Source/Core/AST/SwitchStmt.nll"
					NumbatLogic::Assert::Plz(false);
					if (pTempOffset) delete pTempOffset;
					if (pExpression) delete pExpression;
					if (pSwitchStmt) delete pSwitchStmt;
#line 101 "../../../Source/Core/AST/SwitchStmt.nll"
					return 0;
				}
#line 103 "../../../Source/Core/AST/SwitchStmt.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 105 "../../../Source/Core/AST/SwitchStmt.nll"
				AST* pDefaultStatement = AST::CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
#line 106 "../../../Source/Core/AST/SwitchStmt.nll"
				if (pDefaultStatement == 0)
				{
#line 108 "../../../Source/Core/AST/SwitchStmt.nll"
					Console::Log("expected case statement");
#line 109 "../../../Source/Core/AST/SwitchStmt.nll"
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 110 "../../../Source/Core/AST/SwitchStmt.nll"
					NumbatLogic::Assert::Plz(false);
					if (pDefaultStatement) delete pDefaultStatement;
					if (pTempOffset) delete pTempOffset;
					if (pExpression) delete pExpression;
					if (pSwitchStmt) delete pSwitchStmt;
#line 111 "../../../Source/Core/AST/SwitchStmt.nll"
					return 0;
				}
#line 114 "../../../Source/Core/AST/SwitchStmt.nll"
				AST* pScopedDefaultStatement = 0;
#line 115 "../../../Source/Core/AST/SwitchStmt.nll"
				if (pDefaultStatement->m_eType == AST::Type::AST_SCOPE)
				{
					NumbatLogic::AST* __2021738808 = pDefaultStatement;
#line 116 "../../../Source/Core/AST/SwitchStmt.nll"
					pDefaultStatement = 0;
#line 116 "../../../Source/Core/AST/SwitchStmt.nll"
					pScopedDefaultStatement = __2021738808;
				}
				else
				{
#line 119 "../../../Source/Core/AST/SwitchStmt.nll"
					pScopedDefaultStatement = new Scope();
					NumbatLogic::AST* __2021804401 = pDefaultStatement;
#line 120 "../../../Source/Core/AST/SwitchStmt.nll"
					pDefaultStatement = 0;
#line 120 "../../../Source/Core/AST/SwitchStmt.nll"
					pScopedDefaultStatement->AddChild(__2021804401);
				}
#line 123 "../../../Source/Core/AST/SwitchStmt.nll"
				pSwitchStmt->m_pDefaultStatement = pScopedDefaultStatement;
				NumbatLogic::AST* __4074538021 = pScopedDefaultStatement;
#line 124 "../../../Source/Core/AST/SwitchStmt.nll"
				pScopedDefaultStatement = 0;
#line 124 "../../../Source/Core/AST/SwitchStmt.nll"
				pSwitchStmt->AddChild(__4074538021);
				if (pDefaultStatement) delete pDefaultStatement;
				if (pScopedDefaultStatement) delete pScopedDefaultStatement;
#line 125 "../../../Source/Core/AST/SwitchStmt.nll"
				continue;
			}
#line 128 "../../../Source/Core/AST/SwitchStmt.nll"
			AST* pCaseExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 129 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pCaseExpression == 0)
			{
#line 131 "../../../Source/Core/AST/SwitchStmt.nll"
				Console::Log("expected case expression");
#line 132 "../../../Source/Core/AST/SwitchStmt.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 133 "../../../Source/Core/AST/SwitchStmt.nll"
				NumbatLogic::Assert::Plz(false);
				if (pCaseExpression) delete pCaseExpression;
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pSwitchStmt) delete pSwitchStmt;
#line 134 "../../../Source/Core/AST/SwitchStmt.nll"
				return 0;
			}
#line 136 "../../../Source/Core/AST/SwitchStmt.nll"
			pSwitchStmt->m_pExpressionVector->PushBack(pCaseExpression);
			NumbatLogic::AST* __155144765 = pCaseExpression;
#line 137 "../../../Source/Core/AST/SwitchStmt.nll"
			pCaseExpression = 0;
#line 137 "../../../Source/Core/AST/SwitchStmt.nll"
			pSwitchStmt->AddChild(__155144765);
#line 140 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COLON) == 0)
			{
#line 142 "../../../Source/Core/AST/SwitchStmt.nll"
				Console::Log("expected colon B");
#line 143 "../../../Source/Core/AST/SwitchStmt.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 144 "../../../Source/Core/AST/SwitchStmt.nll"
				NumbatLogic::Assert::Plz(false);
				if (pCaseExpression) delete pCaseExpression;
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pSwitchStmt) delete pSwitchStmt;
#line 145 "../../../Source/Core/AST/SwitchStmt.nll"
				return 0;
			}
#line 147 "../../../Source/Core/AST/SwitchStmt.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 149 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CASE) != 0)
			{
#line 151 "../../../Source/Core/AST/SwitchStmt.nll"
				pSwitchStmt->m_pStatementVector->PushBack(0);
				if (pCaseExpression) delete pCaseExpression;
#line 152 "../../../Source/Core/AST/SwitchStmt.nll"
				continue;
			}
#line 155 "../../../Source/Core/AST/SwitchStmt.nll"
			AST* pCaseStatement = AST::CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
#line 156 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pCaseStatement == 0)
			{
#line 158 "../../../Source/Core/AST/SwitchStmt.nll"
				Console::Log("expected case statement");
#line 159 "../../../Source/Core/AST/SwitchStmt.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 160 "../../../Source/Core/AST/SwitchStmt.nll"
				NumbatLogic::Assert::Plz(false);
				if (pCaseExpression) delete pCaseExpression;
				if (pCaseStatement) delete pCaseStatement;
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				if (pSwitchStmt) delete pSwitchStmt;
#line 161 "../../../Source/Core/AST/SwitchStmt.nll"
				return 0;
			}
#line 164 "../../../Source/Core/AST/SwitchStmt.nll"
			AST* pScopedCaseStatement = 0;
#line 165 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pCaseStatement->m_eType == AST::Type::AST_SCOPE)
			{
				NumbatLogic::AST* __2964786434 = pCaseStatement;
#line 166 "../../../Source/Core/AST/SwitchStmt.nll"
				pCaseStatement = 0;
#line 166 "../../../Source/Core/AST/SwitchStmt.nll"
				pScopedCaseStatement = __2964786434;
			}
			else
			{
#line 169 "../../../Source/Core/AST/SwitchStmt.nll"
				pScopedCaseStatement = new Scope();
				NumbatLogic::AST* __2964852027 = pCaseStatement;
#line 170 "../../../Source/Core/AST/SwitchStmt.nll"
				pCaseStatement = 0;
#line 170 "../../../Source/Core/AST/SwitchStmt.nll"
				pScopedCaseStatement->AddChild(__2964852027);
			}
#line 173 "../../../Source/Core/AST/SwitchStmt.nll"
			pSwitchStmt->m_pStatementVector->PushBack(pScopedCaseStatement);
			NumbatLogic::AST* __1629474447 = pScopedCaseStatement;
#line 174 "../../../Source/Core/AST/SwitchStmt.nll"
			pScopedCaseStatement = 0;
#line 174 "../../../Source/Core/AST/SwitchStmt.nll"
			pSwitchStmt->AddChild(__1629474447);
			if (pCaseExpression) delete pCaseExpression;
			if (pCaseStatement) delete pCaseStatement;
			if (pScopedCaseStatement) delete pScopedCaseStatement;
		}
#line 177 "../../../Source/Core/AST/SwitchStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::SwitchStmt* __1732082662 = pSwitchStmt;
#line 178 "../../../Source/Core/AST/SwitchStmt.nll"
		pSwitchStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 178 "../../../Source/Core/AST/SwitchStmt.nll"
		return __1732082662;
	}

#line 181 "../../../Source/Core/AST/SwitchStmt.nll"
	void SwitchStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 183 "../../../Source/Core/AST/SwitchStmt.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 184 "../../../Source/Core/AST/SwitchStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 186 "../../../Source/Core/AST/SwitchStmt.nll"
		pOutputBuilder->m_sOut->Append("switch (");
#line 187 "../../../Source/Core/AST/SwitchStmt.nll"
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 188 "../../../Source/Core/AST/SwitchStmt.nll"
		pOutputBuilder->m_sOut->Append(")\n");
#line 189 "../../../Source/Core/AST/SwitchStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 190 "../../../Source/Core/AST/SwitchStmt.nll"
		pOutputBuilder->m_sOut->Append("{\n");
#line 191 "../../../Source/Core/AST/SwitchStmt.nll"
		nDepth++;
#line 192 "../../../Source/Core/AST/SwitchStmt.nll"
		for (int i = 0; i < m_pExpressionVector->GetSize(); i++)
		{
#line 194 "../../../Source/Core/AST/SwitchStmt.nll"
			AST* pCaseExpression = m_pExpressionVector->Get(i);
#line 195 "../../../Source/Core/AST/SwitchStmt.nll"
			AST* pCaseStatement = m_pStatementVector->Get(i);
#line 197 "../../../Source/Core/AST/SwitchStmt.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 198 "../../../Source/Core/AST/SwitchStmt.nll"
			pOutputBuilder->m_sOut->Append("case ");
#line 199 "../../../Source/Core/AST/SwitchStmt.nll"
			pCaseExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 200 "../../../Source/Core/AST/SwitchStmt.nll"
			pOutputBuilder->m_sOut->Append(":\n");
#line 201 "../../../Source/Core/AST/SwitchStmt.nll"
			if (pCaseStatement != 0)
			{
#line 203 "../../../Source/Core/AST/SwitchStmt.nll"
				pCaseStatement->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 204 "../../../Source/Core/AST/SwitchStmt.nll"
				pOutputBuilder->m_sOut->Append("\n");
			}
		}
#line 208 "../../../Source/Core/AST/SwitchStmt.nll"
		if (m_pDefaultStatement != 0)
		{
#line 210 "../../../Source/Core/AST/SwitchStmt.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 211 "../../../Source/Core/AST/SwitchStmt.nll"
			pOutputBuilder->m_sOut->Append("default:\n");
#line 212 "../../../Source/Core/AST/SwitchStmt.nll"
			m_pDefaultStatement->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 213 "../../../Source/Core/AST/SwitchStmt.nll"
			pOutputBuilder->m_sOut->Append("\n");
		}
#line 216 "../../../Source/Core/AST/SwitchStmt.nll"
		nDepth--;
#line 217 "../../../Source/Core/AST/SwitchStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 218 "../../../Source/Core/AST/SwitchStmt.nll"
		pOutputBuilder->m_sOut->AppendString("}\n");
	}

#line 3 "../../../Source/Core/AST/SwitchStmt.nll"
	SwitchStmt::~SwitchStmt()
	{
		if (m_pExpressionVector) delete m_pExpressionVector;
		if (m_pStatementVector) delete m_pStatementVector;
	}

}

