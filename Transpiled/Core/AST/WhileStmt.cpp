#include "WhileStmt.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST.hpp"
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
	class Scope;
	class WhileStmt;
	class Util;
	class InternalString;
}
namespace NumbatLogic
{
	WhileStmt::WhileStmt()
	{
		m_pExpression = 0;
		m_pScope = 0;
		m_bStatement = true;
	}

	WhileStmt* WhileStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pWhileToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_WHILE);
		if (pWhileToken == 0)
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
		Scope* pScope = Scope::TryCreate(pTokenContainer, pTempOffset, true);
		if (pScope == 0)
		{
			Console::Log("expected scope");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
		}
		WhileStmt* pWhileStmt = new WhileStmt();
		pWhileStmt->m_eType = AST::Type::AST_WHILE_STMT;
		pWhileStmt->m_pFirstToken = pWhileToken;
		pWhileStmt->m_pExpression = pExpression;
		pWhileStmt->m_pScope = pScope;
		NumbatLogic::AST* __297214760 = pExpression;
		pExpression = 0;
		pWhileStmt->AddChild(__297214760);
		NumbatLogic::Scope* __3242206956 = pScope;
		pScope = 0;
		pWhileStmt->AddChild(__3242206956);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::WhileStmt* __1100338104 = pWhileStmt;
		pWhileStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
		if (pScope) delete pScope;
		return __1100338104;
	}

	void WhileStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		Util::Pad(nDepth, sOut);
		sOut->Append("while (");
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->Append(")\n");
		m_pScope->Stringify(eLanguage, eOutputFile, nDepth, sOut);
	}

}

