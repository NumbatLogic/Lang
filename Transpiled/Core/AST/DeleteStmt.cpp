#include "DeleteStmt.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "ClassDecl.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class DeleteStmt;
	class Validator;
	class ValueType;
	class OutputBuilder;
	class Util;
	class InternalString;
	class ClassDecl;
}
#line 0 "../../../Source/Core/AST/DeleteStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/DeleteStmt.nll"
#line 7 "../../../Source/Core/AST/DeleteStmt.nll"
	DeleteStmt::DeleteStmt()
	{
		m_pExpression = 0;
#line 9 "../../../Source/Core/AST/DeleteStmt.nll"
		m_eType = AST::Type::AST_DELETE_STMT;
		m_bStatement = true;
	}

	DeleteStmt* DeleteStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/DeleteStmt.nll"
		Token* pDeleteToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DELETE);
		if (pDeleteToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 19 "../../../Source/Core/AST/DeleteStmt.nll"
			return 0;
		}
#line 20 "../../../Source/Core/AST/DeleteStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 22 "../../../Source/Core/AST/DeleteStmt.nll"
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pExpression == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 24 "../../../Source/Core/AST/DeleteStmt.nll"
			return 0;
		}
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 27 "../../../Source/Core/AST/DeleteStmt.nll"
			return 0;
		}
#line 28 "../../../Source/Core/AST/DeleteStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 30 "../../../Source/Core/AST/DeleteStmt.nll"
		DeleteStmt* pDelete = new DeleteStmt();
#line 32 "../../../Source/Core/AST/DeleteStmt.nll"
		pDelete->m_pFirstToken = pDeleteToken;
		pDelete->m_pExpression = pExpression;
		NumbatLogic::AST* __1929399914 = pExpression;
		pExpression = 0;
#line 35 "../../../Source/Core/AST/DeleteStmt.nll"
		pDelete->AddChild(__1929399914);
#line 37 "../../../Source/Core/AST/DeleteStmt.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::DeleteStmt* __2565256000 = pDelete;
#line 38 "../../../Source/Core/AST/DeleteStmt.nll"
		pDelete = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 38 "../../../Source/Core/AST/DeleteStmt.nll"
		return __2565256000;
	}

	void DeleteStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
#line 45 "../../../Source/Core/AST/DeleteStmt.nll"
		if (m_pExpression->m_pValueType == 0)
		{
			pValidator->AddError("No valuetype for expression???", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
#line 51 "../../../Source/Core/AST/DeleteStmt.nll"
		if (m_pExpression->m_pValueType->m_pClassDecl != 0)
			AddClassDeclReference(m_pExpression->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
	}

	void DeleteStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 59 "../../../Source/Core/AST/DeleteStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("{\n");
		nDepth++;
#line 63 "../../../Source/Core/AST/DeleteStmt.nll"
		if (eLanguage == AST::Language::CPP)
		{
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
			pOutputBuilder->m_sOut->Append("delete ");
			m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder->m_sOut->Append(";\n");
		}
		else
#line 70 "../../../Source/Core/AST/DeleteStmt.nll"
			if (eLanguage == AST::Language::CS)
			{
				if (m_pExpression->m_pValueType->m_pClassDecl != 0 && m_pExpression->m_pValueType->m_pClassDecl->m_bDisposable)
				{
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
					pOutputBuilder->m_sOut->Append("(");
					m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
					pOutputBuilder->m_sOut->Append(").Dispose();\n");
				}
			}
#line 81 "../../../Source/Core/AST/DeleteStmt.nll"
		if (m_pExpression->m_eType == AST::Type::AST_IDENTIFIER)
		{
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
			m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 86 "../../../Source/Core/AST/DeleteStmt.nll"
			if (eLanguage == AST::Language::CPP)
				pOutputBuilder->m_sOut->Append(" = 0;\n");
			else
				pOutputBuilder->m_sOut->Append(" = null;\n");
		}
#line 92 "../../../Source/Core/AST/DeleteStmt.nll"
		nDepth--;
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("}\n");
	}

}

