#include "IfStmt.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST.hpp"
#include "Scope.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../Util.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Console;
	class Assert;
	class Scope;
	class IfStmt;
	class OutputBuilder;
	class InternalString;
	class Util;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
	IfStmt::IfStmt()
	{
		m_bStatement = true;
	}

	IfStmt* IfStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		Token* pIfToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_IF);
		if (pIfToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
			return 0;
		}
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
			Console::Log("expected left paren");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 28 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		AST* pCondition = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pCondition == 0)
		{
			Console::Log("expected condition");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pCondition) delete pCondition;
#line 34 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
			return 0;
		}
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) == 0)
		{
			Console::Log("expected right paren");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pCondition) delete pCondition;
#line 42 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		Scope* pThenScope = Scope::TryCreate(pTokenContainer, pTempOffset, true);
		if (pThenScope == 0)
		{
			Console::Log("expected then statement / scope");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pCondition) delete pCondition;
			if (pThenScope) delete pThenScope;
#line 52 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
			return 0;
		}
#line 55 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		Scope* pElseScope = 0;
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_ELSE) != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			pElseScope = Scope::TryCreate(pTokenContainer, pTempOffset, true);
			if (pElseScope == 0)
			{
				Console::Log("expected else statement / scope");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pCondition) delete pCondition;
				if (pThenScope) delete pThenScope;
				if (pElseScope) delete pElseScope;
#line 65 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
				return 0;
			}
		}
#line 69 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		IfStmt* pIfStmt = new IfStmt();
#line 71 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		pIfStmt->m_eType = AST::Type::AST_IF_STMT;
		pIfStmt->m_pFirstToken = pIfToken;
		NumbatLogic::AST* __86400392 = pCondition;
		pCondition = 0;
#line 74 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		pIfStmt->AddChild(__86400392);
		NumbatLogic::Scope* __3484778949 = pThenScope;
#line 75 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		pThenScope = 0;
#line 75 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		pIfStmt->AddChild(__3484778949);
		if (pElseScope != 0)
		{
			NumbatLogic::Scope* __1642439819 = pElseScope;
#line 77 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
			pElseScope = 0;
#line 77 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
			pIfStmt->AddChild(__1642439819);
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::IfStmt* __816210157 = pIfStmt;
#line 80 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		pIfStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pCondition) delete pCondition;
		if (pThenScope) delete pThenScope;
		if (pElseScope) delete pElseScope;
#line 80 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		return __816210157;
	}

	void IfStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		AST* pCondition = m_pFirstChild;
		AST* pThen = pCondition->m_pNextSibling;
		AST* pElse = pThen->m_pNextSibling;
#line 89 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		IfStmt* pParentIfStmt = 0;
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_IF_STMT)
			pParentIfStmt = (IfStmt*)(m_pParent);
#line 93 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		if (pParentIfStmt != 0 && pParentIfStmt->m_pFirstChild->m_pNextSibling->m_pNextSibling == this)
			pOutputBuilder->m_sOut->Append(" ");
		else
		{
			pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
		}
#line 101 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		pOutputBuilder->m_sOut->Append("if (");
		pCondition->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		pOutputBuilder->m_sOut->Append(")\n");
		pThen->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		if (pElse != 0)
		{
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
			if (pElse->m_eType == AST::Type::AST_IF_STMT)
			{
				pOutputBuilder->m_sOut->Append("else");
				pElse->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			}
			else
			{
#line 116 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
				pOutputBuilder->m_sOut->Append("else\n");
				pElse->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			}
		}
	}

}

