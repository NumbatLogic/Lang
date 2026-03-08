#include "ReturnStmt.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../Validator.hpp"
#include "../Util.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class ReturnStmt;
	class Validator;
	class Util;
	class OutputBuilder;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/ReturnStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ReturnStmt.nll"
	ReturnStmt::ReturnStmt()
	{
		m_pExpression = 0;
		m_eType = AST::Type::AST_RETURN_STMT;
		m_bStatement = true;
	}

	ReturnStmt* ReturnStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pReturnToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_RETURN);
		if (pReturnToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ReturnStmt* pReturnStmt = new ReturnStmt();
		pReturnStmt->m_pFirstToken = pReturnToken;
		pReturnStmt->m_pExpression = pExpression;
		if (pExpression != 0)
		{
			NumbatLogic::AST* __1929399913 = pExpression;
			pExpression = 0;
			pReturnStmt->AddChild(__1929399913);
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ReturnStmt* __2739522412 = pReturnStmt;
		pReturnStmt = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
		return __2739522412;
	}

	void ReturnStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		pValidator->InjectCleanup(this);
	}

	void ReturnStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out)
	{
		Util::Pad(nDepth, out->m_sOut);
		out->m_sOut->AppendString("return");
		if (m_pExpression != 0)
		{
			out->m_sOut->AppendChar(' ');
			m_pExpression->Stringify(eLanguage, eOutputFile, 0, out);
		}
		out->m_sOut->AppendString(";\n");
	}

}

