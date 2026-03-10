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
#line 0 "../../../Source/Core/AST/IfStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/IfStmt.nll"
#line 5 "../../../Source/Core/AST/IfStmt.nll"
	IfStmt::IfStmt()
	{
#line 7 "../../../Source/Core/AST/IfStmt.nll"
		m_bStatement = true;
	}

#line 10 "../../../Source/Core/AST/IfStmt.nll"
	IfStmt* IfStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
#line 12 "../../../Source/Core/AST/IfStmt.nll"
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 14 "../../../Source/Core/AST/IfStmt.nll"
		Token* pIfToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_IF);
#line 15 "../../../Source/Core/AST/IfStmt.nll"
		if (pIfToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 16 "../../../Source/Core/AST/IfStmt.nll"
			return 0;
		}
#line 17 "../../../Source/Core/AST/IfStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 19 "../../../Source/Core/AST/IfStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
#line 21 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log("expected left paren");
#line 22 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 23 "../../../Source/Core/AST/IfStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 24 "../../../Source/Core/AST/IfStmt.nll"
			return 0;
		}
#line 26 "../../../Source/Core/AST/IfStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 28 "../../../Source/Core/AST/IfStmt.nll"
		AST* pCondition = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 29 "../../../Source/Core/AST/IfStmt.nll"
		if (pCondition == 0)
		{
#line 31 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log("expected condition");
#line 32 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 33 "../../../Source/Core/AST/IfStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pCondition) delete pCondition;
#line 34 "../../../Source/Core/AST/IfStmt.nll"
			return 0;
		}
#line 37 "../../../Source/Core/AST/IfStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) == 0)
		{
#line 39 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log("expected right paren");
#line 40 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 41 "../../../Source/Core/AST/IfStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pCondition) delete pCondition;
#line 42 "../../../Source/Core/AST/IfStmt.nll"
			return 0;
		}
#line 44 "../../../Source/Core/AST/IfStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 46 "../../../Source/Core/AST/IfStmt.nll"
		Scope* pThenScope = Scope::TryCreate(pTokenContainer, pTempOffset, true);
#line 47 "../../../Source/Core/AST/IfStmt.nll"
		if (pThenScope == 0)
		{
#line 49 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log("expected then statement / scope");
#line 50 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 51 "../../../Source/Core/AST/IfStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pCondition) delete pCondition;
			if (pThenScope) delete pThenScope;
#line 52 "../../../Source/Core/AST/IfStmt.nll"
			return 0;
		}
#line 55 "../../../Source/Core/AST/IfStmt.nll"
		Scope* pElseScope = 0;
#line 56 "../../../Source/Core/AST/IfStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_ELSE) != 0)
		{
#line 58 "../../../Source/Core/AST/IfStmt.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 59 "../../../Source/Core/AST/IfStmt.nll"
			pElseScope = Scope::TryCreate(pTokenContainer, pTempOffset, true);
#line 60 "../../../Source/Core/AST/IfStmt.nll"
			if (pElseScope == 0)
			{
#line 62 "../../../Source/Core/AST/IfStmt.nll"
				Console::Log("expected else statement / scope");
#line 63 "../../../Source/Core/AST/IfStmt.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 64 "../../../Source/Core/AST/IfStmt.nll"
				NumbatLogic::Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pCondition) delete pCondition;
				if (pThenScope) delete pThenScope;
				if (pElseScope) delete pElseScope;
#line 65 "../../../Source/Core/AST/IfStmt.nll"
				return 0;
			}
		}
#line 69 "../../../Source/Core/AST/IfStmt.nll"
		IfStmt* pIfStmt = new IfStmt();
#line 71 "../../../Source/Core/AST/IfStmt.nll"
		pIfStmt->m_eType = AST::Type::AST_IF_STMT;
#line 72 "../../../Source/Core/AST/IfStmt.nll"
		pIfStmt->m_pFirstToken = pIfToken;
		NumbatLogic::AST* __86400392 = pCondition;
#line 74 "../../../Source/Core/AST/IfStmt.nll"
		pCondition = 0;
#line 74 "../../../Source/Core/AST/IfStmt.nll"
		pIfStmt->AddChild(__86400392);
		NumbatLogic::Scope* __3484778949 = pThenScope;
#line 75 "../../../Source/Core/AST/IfStmt.nll"
		pThenScope = 0;
#line 75 "../../../Source/Core/AST/IfStmt.nll"
		pIfStmt->AddChild(__3484778949);
#line 76 "../../../Source/Core/AST/IfStmt.nll"
		if (pElseScope != 0)
		{
			NumbatLogic::Scope* __1642439819 = pElseScope;
#line 77 "../../../Source/Core/AST/IfStmt.nll"
			pElseScope = 0;
#line 77 "../../../Source/Core/AST/IfStmt.nll"
			pIfStmt->AddChild(__1642439819);
		}
#line 79 "../../../Source/Core/AST/IfStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::IfStmt* __816210157 = pIfStmt;
#line 80 "../../../Source/Core/AST/IfStmt.nll"
		pIfStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pCondition) delete pCondition;
		if (pThenScope) delete pThenScope;
		if (pElseScope) delete pElseScope;
#line 80 "../../../Source/Core/AST/IfStmt.nll"
		return __816210157;
	}

#line 83 "../../../Source/Core/AST/IfStmt.nll"
	void IfStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 85 "../../../Source/Core/AST/IfStmt.nll"
		AST* pCondition = m_pFirstChild;
#line 86 "../../../Source/Core/AST/IfStmt.nll"
		AST* pThen = pCondition->m_pNextSibling;
#line 87 "../../../Source/Core/AST/IfStmt.nll"
		AST* pElse = pThen->m_pNextSibling;
#line 89 "../../../Source/Core/AST/IfStmt.nll"
		IfStmt* pParentIfStmt = 0;
#line 90 "../../../Source/Core/AST/IfStmt.nll"
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_IF_STMT)
#line 91 "../../../Source/Core/AST/IfStmt.nll"
			pParentIfStmt = (IfStmt*)(m_pParent);
#line 93 "../../../Source/Core/AST/IfStmt.nll"
		if (pParentIfStmt != 0 && pParentIfStmt->m_pFirstChild->m_pNextSibling->m_pNextSibling == this)
#line 94 "../../../Source/Core/AST/IfStmt.nll"
			pOutputBuilder->m_sOut->Append(" ");
		else
		{
#line 97 "../../../Source/Core/AST/IfStmt.nll"
			pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 98 "../../../Source/Core/AST/IfStmt.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
		}
#line 101 "../../../Source/Core/AST/IfStmt.nll"
		pOutputBuilder->m_sOut->Append("if (");
#line 102 "../../../Source/Core/AST/IfStmt.nll"
		pCondition->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 103 "../../../Source/Core/AST/IfStmt.nll"
		pOutputBuilder->m_sOut->Append(")\n");
#line 104 "../../../Source/Core/AST/IfStmt.nll"
		pThen->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 105 "../../../Source/Core/AST/IfStmt.nll"
		if (pElse != 0)
		{
#line 107 "../../../Source/Core/AST/IfStmt.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 108 "../../../Source/Core/AST/IfStmt.nll"
			if (pElse->m_eType == AST::Type::AST_IF_STMT)
			{
#line 110 "../../../Source/Core/AST/IfStmt.nll"
				pOutputBuilder->m_sOut->Append("else");
#line 111 "../../../Source/Core/AST/IfStmt.nll"
				pElse->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			}
			else
			{
#line 116 "../../../Source/Core/AST/IfStmt.nll"
				pOutputBuilder->m_sOut->Append("else\n");
#line 117 "../../../Source/Core/AST/IfStmt.nll"
				pElse->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			}
		}
	}

}

