#include "ExpressionStmt.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class TokenContainer;
	class Token;
	class ExpressionStmt;
	class OutputBuilder;
	class Util;
	class InternalString;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
	ExpressionStmt::ExpressionStmt()
	{
		m_pExpression = 0;
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
		m_eType = AST::Type::AST_EXPRESSION_STMT;
		m_bStatement = true;
	}

	ExpressionStmt* ExpressionStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pExpression == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
			return 0;
		}
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
			return 0;
		}
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
		ExpressionStmt* pExpressionStmt = new ExpressionStmt();
		pExpressionStmt->m_pFirstToken = pExpression->m_pFirstToken;
		pExpressionStmt->m_pExpression = pExpression;
		NumbatLogic::AST* __1929334319 = pExpression;
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
		pExpression = 0;
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
		pExpressionStmt->AddChild(__1929334319);
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ExpressionStmt* __490873359 = pExpressionStmt;
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
		pExpressionStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
		return __490873359;
	}

	void ExpressionStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/ExpressionStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		m_pExpression->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		pOutputBuilder->m_sOut->Append(";\n");
	}

}

