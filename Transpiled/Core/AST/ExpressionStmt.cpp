#include "ExpressionStmt.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class TokenContainer;
	class Token;
	class ExpressionStmt;
	class Util;
	class InternalString;
}
namespace NumbatLogic
{
	ExpressionStmt::ExpressionStmt()
	{
		m_pExpression = 0;
		m_eType = AST::Type::AST_EXPRESSION_STMT;
		m_bStatement = true;
	}

	ExpressionStmt* ExpressionStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pExpression == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
			return 0;
		}
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ExpressionStmt* pExpressionStmt = new ExpressionStmt();
		pExpressionStmt->m_pFirstToken = pExpression->m_pFirstToken;
		pExpressionStmt->m_pExpression = pExpression;
		NumbatLogic::AST* __297214788 = pExpression;
		pExpression = 0;
		pExpressionStmt->AddChild(__297214788);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ExpressionStmt* __3072594936 = pExpressionStmt;
		pExpressionStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
		return __3072594936;
	}

	void ExpressionStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		Util::Pad(nDepth, sOut);
		m_pExpression->Stringify(eLanguage, eOutputFile, nDepth, sOut);
		sOut->Append(";\n");
	}

}

