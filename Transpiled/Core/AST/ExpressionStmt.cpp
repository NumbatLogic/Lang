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
#line 1 "../../../Source/Core/AST/ExpressionStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/ExpressionStmt.nll"
#line 8 "../../../Source/Core/AST/ExpressionStmt.nll"
	ExpressionStmt::ExpressionStmt()
	{
		m_pExpression = 0;
#line 10 "../../../Source/Core/AST/ExpressionStmt.nll"
		m_eType = AST::Type::AST_EXPRESSION_STMT;
#line 11 "../../../Source/Core/AST/ExpressionStmt.nll"
		m_bStatement = true;
	}

#line 14 "../../../Source/Core/AST/ExpressionStmt.nll"
	ExpressionStmt* ExpressionStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 19 "../../../Source/Core/AST/ExpressionStmt.nll"
		if (pExpression == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 20 "../../../Source/Core/AST/ExpressionStmt.nll"
			return 0;
		}
#line 22 "../../../Source/Core/AST/ExpressionStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 23 "../../../Source/Core/AST/ExpressionStmt.nll"
			return 0;
		}
#line 24 "../../../Source/Core/AST/ExpressionStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ExpressionStmt* pExpressionStmt = new ExpressionStmt();
#line 28 "../../../Source/Core/AST/ExpressionStmt.nll"
		pExpressionStmt->m_pFirstToken = pExpression->m_pFirstToken;
#line 29 "../../../Source/Core/AST/ExpressionStmt.nll"
		pExpressionStmt->m_pExpression = pExpression;
		NumbatLogic::AST* __1929334319 = pExpression;
#line 30 "../../../Source/Core/AST/ExpressionStmt.nll"
		pExpression = 0;
#line 30 "../../../Source/Core/AST/ExpressionStmt.nll"
		pExpressionStmt->AddChild(__1929334319);
#line 32 "../../../Source/Core/AST/ExpressionStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ExpressionStmt* __490873359 = pExpressionStmt;
#line 33 "../../../Source/Core/AST/ExpressionStmt.nll"
		pExpressionStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 33 "../../../Source/Core/AST/ExpressionStmt.nll"
		return __490873359;
	}

#line 36 "../../../Source/Core/AST/ExpressionStmt.nll"
	void ExpressionStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 38 "../../../Source/Core/AST/ExpressionStmt.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 40 "../../../Source/Core/AST/ExpressionStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 41 "../../../Source/Core/AST/ExpressionStmt.nll"
		m_pExpression->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 42 "../../../Source/Core/AST/ExpressionStmt.nll"
		pOutputBuilder->m_sOut->Append(";\n");
	}

}

