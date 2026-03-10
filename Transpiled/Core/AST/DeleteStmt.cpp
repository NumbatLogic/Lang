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
#line 10 "../../../Source/Core/AST/DeleteStmt.nll"
		m_bStatement = true;
	}

#line 13 "../../../Source/Core/AST/DeleteStmt.nll"
	DeleteStmt* DeleteStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pDeleteToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DELETE);
#line 18 "../../../Source/Core/AST/DeleteStmt.nll"
		if (pDeleteToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 19 "../../../Source/Core/AST/DeleteStmt.nll"
			return 0;
		}
#line 20 "../../../Source/Core/AST/DeleteStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 23 "../../../Source/Core/AST/DeleteStmt.nll"
		if (pExpression == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 24 "../../../Source/Core/AST/DeleteStmt.nll"
			return 0;
		}
#line 26 "../../../Source/Core/AST/DeleteStmt.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 27 "../../../Source/Core/AST/DeleteStmt.nll"
			return 0;
		}
#line 28 "../../../Source/Core/AST/DeleteStmt.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		DeleteStmt* pDelete = new DeleteStmt();
#line 32 "../../../Source/Core/AST/DeleteStmt.nll"
		pDelete->m_pFirstToken = pDeleteToken;
#line 33 "../../../Source/Core/AST/DeleteStmt.nll"
		pDelete->m_pExpression = pExpression;
		NumbatLogic::AST* __1929399914 = pExpression;
#line 35 "../../../Source/Core/AST/DeleteStmt.nll"
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

#line 41 "../../../Source/Core/AST/DeleteStmt.nll"
	void DeleteStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 43 "../../../Source/Core/AST/DeleteStmt.nll"
		AST::Validate(pValidator, pParent);
#line 45 "../../../Source/Core/AST/DeleteStmt.nll"
		if (m_pExpression->m_pValueType == 0)
		{
#line 47 "../../../Source/Core/AST/DeleteStmt.nll"
			pValidator->AddError("No valuetype for expression???", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
#line 48 "../../../Source/Core/AST/DeleteStmt.nll"
			return;
		}
#line 51 "../../../Source/Core/AST/DeleteStmt.nll"
		if (m_pExpression->m_pValueType->m_pClassDecl != 0)
#line 52 "../../../Source/Core/AST/DeleteStmt.nll"
			AddClassDeclReference(m_pExpression->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
	}

#line 55 "../../../Source/Core/AST/DeleteStmt.nll"
	void DeleteStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 57 "../../../Source/Core/AST/DeleteStmt.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 59 "../../../Source/Core/AST/DeleteStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 60 "../../../Source/Core/AST/DeleteStmt.nll"
		pOutputBuilder->m_sOut->Append("{\n");
#line 61 "../../../Source/Core/AST/DeleteStmt.nll"
		nDepth++;
#line 63 "../../../Source/Core/AST/DeleteStmt.nll"
		if (eLanguage == AST::Language::CPP)
		{
#line 65 "../../../Source/Core/AST/DeleteStmt.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 66 "../../../Source/Core/AST/DeleteStmt.nll"
			pOutputBuilder->m_sOut->Append("delete ");
#line 67 "../../../Source/Core/AST/DeleteStmt.nll"
			m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 68 "../../../Source/Core/AST/DeleteStmt.nll"
			pOutputBuilder->m_sOut->Append(";\n");
		}
		else
#line 70 "../../../Source/Core/AST/DeleteStmt.nll"
			if (eLanguage == AST::Language::CS)
			{
#line 72 "../../../Source/Core/AST/DeleteStmt.nll"
				if (m_pExpression->m_pValueType->m_pClassDecl != 0 && m_pExpression->m_pValueType->m_pClassDecl->m_bDisposable)
				{
#line 74 "../../../Source/Core/AST/DeleteStmt.nll"
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 75 "../../../Source/Core/AST/DeleteStmt.nll"
					pOutputBuilder->m_sOut->Append("(");
#line 76 "../../../Source/Core/AST/DeleteStmt.nll"
					m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 77 "../../../Source/Core/AST/DeleteStmt.nll"
					pOutputBuilder->m_sOut->Append(").Dispose();\n");
				}
			}
#line 81 "../../../Source/Core/AST/DeleteStmt.nll"
		if (m_pExpression->m_eType == AST::Type::AST_IDENTIFIER)
		{
#line 83 "../../../Source/Core/AST/DeleteStmt.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 84 "../../../Source/Core/AST/DeleteStmt.nll"
			m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 86 "../../../Source/Core/AST/DeleteStmt.nll"
			if (eLanguage == AST::Language::CPP)
#line 87 "../../../Source/Core/AST/DeleteStmt.nll"
				pOutputBuilder->m_sOut->Append(" = 0;\n");
			else
#line 89 "../../../Source/Core/AST/DeleteStmt.nll"
				pOutputBuilder->m_sOut->Append(" = null;\n");
		}
#line 92 "../../../Source/Core/AST/DeleteStmt.nll"
		nDepth--;
#line 93 "../../../Source/Core/AST/DeleteStmt.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 94 "../../../Source/Core/AST/DeleteStmt.nll"
		pOutputBuilder->m_sOut->Append("}\n");
	}

}

