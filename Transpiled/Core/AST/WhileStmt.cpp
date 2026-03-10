#include "WhileStmt.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST.hpp"
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
	class Scope;
	class WhileStmt;
	class OutputBuilder;
	class Util;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/WhileStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/WhileStmt.nll"
#line 8 "../../../Source/Core/AST/WhileStmt.nll"
	WhileStmt::WhileStmt()
	{
		m_pExpression = 0;
		m_pScope = 0;
#line 10 "../../../Source/Core/AST/WhileStmt.nll"
		m_bStatement = true;
	}

#line 13 "../../../Source/Core/AST/WhileStmt.nll"
	WhileStmt* WhileStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pWhileToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_WHILE);
#line 18 "../../../Source/Core/AST/WhileStmt.nll"
		if (pWhileToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 19 "../../../Source/Core/AST/WhileStmt.nll"
			return 0;
		}
#line 20 "../../../Source/Core/AST/WhileStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 22 "../../../Source/Core/AST/WhileStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
#line 24 "../../../Source/Core/AST/WhileStmt.nll"
			Console::Log("expected left paren");
#line 25 "../../../Source/Core/AST/WhileStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 26 "../../../Source/Core/AST/WhileStmt.nll"
			return 0;
		}
#line 28 "../../../Source/Core/AST/WhileStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 31 "../../../Source/Core/AST/WhileStmt.nll"
		if (pExpression == 0)
		{
#line 33 "../../../Source/Core/AST/WhileStmt.nll"
			Console::Log("expected expression");
#line 34 "../../../Source/Core/AST/WhileStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 35 "../../../Source/Core/AST/WhileStmt.nll"
			return 0;
		}
#line 38 "../../../Source/Core/AST/WhileStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) == 0)
		{
#line 40 "../../../Source/Core/AST/WhileStmt.nll"
			Console::Log("expected right paren");
#line 41 "../../../Source/Core/AST/WhileStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 42 "../../../Source/Core/AST/WhileStmt.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 43 "../../../Source/Core/AST/WhileStmt.nll"
			return 0;
		}
#line 45 "../../../Source/Core/AST/WhileStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		Scope* pScope = Scope::TryCreate(pTokenContainer, pTempOffset, true);
#line 48 "../../../Source/Core/AST/WhileStmt.nll"
		if (pScope == 0)
		{
#line 50 "../../../Source/Core/AST/WhileStmt.nll"
			Console::Log("expected scope");
#line 51 "../../../Source/Core/AST/WhileStmt.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 52 "../../../Source/Core/AST/WhileStmt.nll"
			NumbatLogic::Assert::Plz(false);
		}
		WhileStmt* pWhileStmt = new WhileStmt();
#line 57 "../../../Source/Core/AST/WhileStmt.nll"
		pWhileStmt->m_eType = AST::Type::AST_WHILE_STMT;
#line 58 "../../../Source/Core/AST/WhileStmt.nll"
		pWhileStmt->m_pFirstToken = pWhileToken;
#line 59 "../../../Source/Core/AST/WhileStmt.nll"
		pWhileStmt->m_pExpression = pExpression;
#line 60 "../../../Source/Core/AST/WhileStmt.nll"
		pWhileStmt->m_pScope = pScope;
		NumbatLogic::AST* __1929596708 = pExpression;
#line 62 "../../../Source/Core/AST/WhileStmt.nll"
		pExpression = 0;
#line 62 "../../../Source/Core/AST/WhileStmt.nll"
		pWhileStmt->AddChild(__1929596708);
		NumbatLogic::Scope* __1530749729 = pScope;
#line 63 "../../../Source/Core/AST/WhileStmt.nll"
		pScope = 0;
#line 63 "../../../Source/Core/AST/WhileStmt.nll"
		pWhileStmt->AddChild(__1530749729);
#line 65 "../../../Source/Core/AST/WhileStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::WhileStmt* __2238546185 = pWhileStmt;
#line 66 "../../../Source/Core/AST/WhileStmt.nll"
		pWhileStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
		if (pScope) delete pScope;
#line 66 "../../../Source/Core/AST/WhileStmt.nll"
		return __2238546185;
	}

#line 69 "../../../Source/Core/AST/WhileStmt.nll"
	void WhileStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 71 "../../../Source/Core/AST/WhileStmt.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 72 "../../../Source/Core/AST/WhileStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 74 "../../../Source/Core/AST/WhileStmt.nll"
		pOutputBuilder->m_sOut->Append("while (");
#line 75 "../../../Source/Core/AST/WhileStmt.nll"
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 76 "../../../Source/Core/AST/WhileStmt.nll"
		pOutputBuilder->m_sOut->Append(")\n");
#line 77 "../../../Source/Core/AST/WhileStmt.nll"
		m_pScope->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
	}

}

