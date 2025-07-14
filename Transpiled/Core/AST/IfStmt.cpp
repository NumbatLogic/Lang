#include "IfStmt.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST.hpp"
#include "Scope.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../Util.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Console;
	class Assert;
	class AST;
	class Scope;
	class IfStmt;
	class InternalString;
	class Util;
}
namespace NumbatLogic
{
	IfStmt::IfStmt()
	{
		m_bStatement = true;
	}

	IfStmt* IfStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pIfToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_IF);
		if (pIfToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
			Console::Log("expected left paren");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pCondition = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pCondition == 0)
		{
			Console::Log("expected condition");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pCondition) delete pCondition;
			return 0;
		}
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) == 0)
		{
			Console::Log("expected right paren");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pCondition) delete pCondition;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		Scope* pThenScope = Scope::TryCreate(pTokenContainer, pTempOffset, true);
		if (pThenScope == 0)
		{
			Console::Log("expected then statement / scope");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pCondition) delete pCondition;
			if (pThenScope) delete pThenScope;
			return 0;
		}
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
				return 0;
			}
		}
		IfStmt* pIfStmt = new IfStmt();
		pIfStmt->m_eType = AST::Type::AST_IF_STMT;
		pIfStmt->m_pFirstToken = pIfToken;
		NumbatLogic::AST* __2644810379 = pCondition;
		pCondition = 0;
		pIfStmt->AddChild(__2644810379);
		NumbatLogic::Scope* __2674729639 = pThenScope;
		pThenScope = 0;
		pIfStmt->AddChild(__2674729639);
		if (pElseScope != 0)
		{
			NumbatLogic::Scope* __1462073918 = pElseScope;
			pElseScope = 0;
			pIfStmt->AddChild(__1462073918);
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::IfStmt* __963526345 = pIfStmt;
		pIfStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pCondition) delete pCondition;
		if (pThenScope) delete pThenScope;
		if (pElseScope) delete pElseScope;
		return __963526345;
	}

	void IfStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		AST* pCondition = m_pFirstChild;
		AST* pThen = pCondition->m_pNextSibling;
		AST* pElse = pThen->m_pNextSibling;
		IfStmt* pParentIfStmt = 0;
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_IF_STMT)
			pParentIfStmt = (IfStmt*)(m_pParent);
		if (pParentIfStmt != 0 && pParentIfStmt->m_pFirstChild->m_pNextSibling->m_pNextSibling == this)
			sOut->Append(" ");
		else
			Util::Pad(nDepth, sOut);
		sOut->Append("if (");
		pCondition->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->Append(")\n");
		pThen->Stringify(eLanguage, eOutputFile, nDepth, sOut);
		if (pElse != 0)
		{
			Util::Pad(nDepth, sOut);
			if (pElse->m_eType == AST::Type::AST_IF_STMT)
			{
				sOut->Append("else");
				pElse->Stringify(eLanguage, eOutputFile, nDepth, sOut);
			}
			else
			{
				sOut->Append("else\n");
				pElse->Stringify(eLanguage, eOutputFile, nDepth, sOut);
			}
		}
	}

}

