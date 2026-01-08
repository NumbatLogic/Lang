#include "DeleteStmt.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
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
	class Util;
	class InternalString;
	class ClassDecl;
}
namespace NumbatLogic
{
	DeleteStmt::DeleteStmt()
	{
		m_pExpression = 0;
		m_eType = AST::Type::AST_DELETE_STMT;
		m_bStatement = true;
	}

	DeleteStmt* DeleteStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pDeleteToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DELETE);
		if (pDeleteToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
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
		DeleteStmt* pDelete = new DeleteStmt();
		pDelete->m_pFirstToken = pDeleteToken;
		pDelete->m_pExpression = pExpression;
		NumbatLogic::AST* __1929399914 = pExpression;
		pExpression = 0;
		pDelete->AddChild(__1929399914);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::DeleteStmt* __2565256000 = pDelete;
		pDelete = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
		return __2565256000;
	}

	void DeleteStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		if (m_pExpression->m_pValueType == 0)
		{
			pValidator->AddError("No valuetype for expression???", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
		if (m_pExpression->m_pValueType->m_pClassDecl != 0)
			AddClassDeclReference(m_pExpression->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
	}

	void DeleteStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		Util::Pad(nDepth, sOut);
		sOut->Append("{\n");
		nDepth++;
		if (eLanguage == AST::Language::CPP)
		{
			Util::Pad(nDepth, sOut);
			sOut->Append("delete ");
			m_pExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut->Append(";\n");
		}
		else
			if (eLanguage == AST::Language::CS)
			{
				if (m_pExpression->m_pValueType->m_pClassDecl != 0 && m_pExpression->m_pValueType->m_pClassDecl->m_bDisposable)
				{
					Util::Pad(nDepth, sOut);
					sOut->Append("(");
					m_pExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
					sOut->Append(").Dispose();\n");
				}
			}
		if (m_pExpression->m_eType == AST::Type::AST_IDENTIFIER)
		{
			Util::Pad(nDepth, sOut);
			m_pExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
			if (eLanguage == AST::Language::CPP)
				sOut->Append(" = 0;\n");
			else
				sOut->Append(" = null;\n");
		}
		nDepth--;
		Util::Pad(nDepth, sOut);
		sOut->Append("}\n");
	}

}

