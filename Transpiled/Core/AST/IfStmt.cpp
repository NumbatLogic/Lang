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
#line 1 "../../../Source/Core/AST/IfStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/IfStmt.nll"
#line 6 "../../../Source/Core/AST/IfStmt.nll"
	IfStmt::IfStmt()
	{
#line 8 "../../../Source/Core/AST/IfStmt.nll"
		m_bStatement = true;
	}

#line 11 "../../../Source/Core/AST/IfStmt.nll"
	IfStmt* IfStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pIfToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_IF);
#line 16 "../../../Source/Core/AST/IfStmt.nll"
		if (pIfToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 17 "../../../Source/Core/AST/IfStmt.nll"
			return 0;
		}
#line 18 "../../../Source/Core/AST/IfStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 20 "../../../Source/Core/AST/IfStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
#line 22 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log("expected left paren");
#line 23 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 24 "../../../Source/Core/AST/IfStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 25 "../../../Source/Core/AST/IfStmt.nll"
			return 0;
		}
#line 27 "../../../Source/Core/AST/IfStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pCondition = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 30 "../../../Source/Core/AST/IfStmt.nll"
		if (pCondition == 0)
		{
#line 32 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log("expected condition");
#line 33 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 34 "../../../Source/Core/AST/IfStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pCondition) delete pCondition;
#line 35 "../../../Source/Core/AST/IfStmt.nll"
			return 0;
		}
#line 38 "../../../Source/Core/AST/IfStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) == 0)
		{
#line 40 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log("expected right paren");
#line 41 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 42 "../../../Source/Core/AST/IfStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pCondition) delete pCondition;
#line 43 "../../../Source/Core/AST/IfStmt.nll"
			return 0;
		}
#line 45 "../../../Source/Core/AST/IfStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		Scope* pThenScope = Scope::TryCreate(pTokenContainer, pTempOffset, true);
#line 48 "../../../Source/Core/AST/IfStmt.nll"
		if (pThenScope == 0)
		{
#line 50 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log("expected then statement / scope");
#line 51 "../../../Source/Core/AST/IfStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 52 "../../../Source/Core/AST/IfStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pCondition) delete pCondition;
			if (pThenScope) delete pThenScope;
#line 53 "../../../Source/Core/AST/IfStmt.nll"
			return 0;
		}
		Scope* pElseScope = 0;
#line 57 "../../../Source/Core/AST/IfStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_ELSE) != 0)
		{
#line 59 "../../../Source/Core/AST/IfStmt.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 60 "../../../Source/Core/AST/IfStmt.nll"
			pElseScope = Scope::TryCreate(pTokenContainer, pTempOffset, true);
#line 61 "../../../Source/Core/AST/IfStmt.nll"
			if (pElseScope == 0)
			{
#line 63 "../../../Source/Core/AST/IfStmt.nll"
				Console::Log("expected else statement / scope");
#line 64 "../../../Source/Core/AST/IfStmt.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 65 "../../../Source/Core/AST/IfStmt.nll"
				NumbatLogic::Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pCondition) delete pCondition;
				if (pThenScope) delete pThenScope;
				if (pElseScope) delete pElseScope;
#line 66 "../../../Source/Core/AST/IfStmt.nll"
				return 0;
			}
		}
		IfStmt* pIfStmt = new IfStmt();
#line 72 "../../../Source/Core/AST/IfStmt.nll"
		pIfStmt->m_eType = AST::Type::AST_IF_STMT;
#line 73 "../../../Source/Core/AST/IfStmt.nll"
		pIfStmt->m_pFirstToken = pIfToken;
		NumbatLogic::AST* __86400392 = pCondition;
#line 75 "../../../Source/Core/AST/IfStmt.nll"
		pCondition = 0;
#line 75 "../../../Source/Core/AST/IfStmt.nll"
		pIfStmt->AddChild(__86400392);
		NumbatLogic::Scope* __3484778949 = pThenScope;
#line 76 "../../../Source/Core/AST/IfStmt.nll"
		pThenScope = 0;
#line 76 "../../../Source/Core/AST/IfStmt.nll"
		pIfStmt->AddChild(__3484778949);
#line 77 "../../../Source/Core/AST/IfStmt.nll"
		if (pElseScope != 0)
		{
			NumbatLogic::Scope* __1642439819 = pElseScope;
#line 78 "../../../Source/Core/AST/IfStmt.nll"
			pElseScope = 0;
#line 78 "../../../Source/Core/AST/IfStmt.nll"
			pIfStmt->AddChild(__1642439819);
		}
#line 80 "../../../Source/Core/AST/IfStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::IfStmt* __816210157 = pIfStmt;
#line 81 "../../../Source/Core/AST/IfStmt.nll"
		pIfStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pCondition) delete pCondition;
		if (pThenScope) delete pThenScope;
		if (pElseScope) delete pElseScope;
#line 81 "../../../Source/Core/AST/IfStmt.nll"
		return __816210157;
	}

#line 84 "../../../Source/Core/AST/IfStmt.nll"
	void IfStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		AST* pCondition = m_pFirstChild;
		AST* pThen = pCondition->m_pNextSibling;
		AST* pElse = pThen->m_pNextSibling;
		IfStmt* pParentIfStmt = 0;
#line 91 "../../../Source/Core/AST/IfStmt.nll"
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_IF_STMT)
#line 92 "../../../Source/Core/AST/IfStmt.nll"
			pParentIfStmt = (IfStmt*)(m_pParent);
#line 94 "../../../Source/Core/AST/IfStmt.nll"
		if (pParentIfStmt != 0 && pParentIfStmt->m_pFirstChild->m_pNextSibling->m_pNextSibling == this)
#line 95 "../../../Source/Core/AST/IfStmt.nll"
			pOutputBuilder->m_sOut->Append(" ");
		else
		{
#line 98 "../../../Source/Core/AST/IfStmt.nll"
			pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 99 "../../../Source/Core/AST/IfStmt.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
		}
#line 102 "../../../Source/Core/AST/IfStmt.nll"
		pOutputBuilder->m_sOut->Append("if (");
#line 103 "../../../Source/Core/AST/IfStmt.nll"
		pCondition->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 104 "../../../Source/Core/AST/IfStmt.nll"
		pOutputBuilder->m_sOut->Append(")\n");
#line 105 "../../../Source/Core/AST/IfStmt.nll"
		pThen->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 106 "../../../Source/Core/AST/IfStmt.nll"
		if (pElse != 0)
		{
#line 108 "../../../Source/Core/AST/IfStmt.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 109 "../../../Source/Core/AST/IfStmt.nll"
			if (pElse->m_eType == AST::Type::AST_IF_STMT)
			{
#line 111 "../../../Source/Core/AST/IfStmt.nll"
				pOutputBuilder->m_sOut->Append("else");
#line 112 "../../../Source/Core/AST/IfStmt.nll"
				pElse->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			}
			else
			{
#line 117 "../../../Source/Core/AST/IfStmt.nll"
				pOutputBuilder->m_sOut->Append("else\n");
#line 118 "../../../Source/Core/AST/IfStmt.nll"
				pElse->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			}
		}
	}

}

