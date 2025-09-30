#include "DisownExpr.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../Util.hpp"
#include "VarDecl.hpp"
#include "NullExpr.hpp"
#include "OperatorExpr.hpp"
#include "ExpressionStmt.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Console;
	class Assert;
	class DisownExpr;
	class Validator;
	class ValueType;
	class InternalString;
	class Util;
	class TypeRef;
	class VarDecl;
	class NullExpr;
	class OperatorExpr;
	class ExpressionStmt;
}
namespace NumbatLogic
{
	DisownExpr::DisownExpr()
	{
		m_pExpression = 0;
		m_sTempVarName = 0;
		m_eType = AST::Type::AST_DISOWN_EXP;
	}

	DisownExpr* DisownExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pDisownToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DISOWN);
		if (pDisownToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pExpression == 0)
		{
			Console::Log("expected expresssion");
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
			return 0;
		}
		DisownExpr* pDisownExpr = new DisownExpr();
		pDisownExpr->m_pFirstToken = pDisownToken;
		pDisownExpr->m_pExpression = pExpression;
		NumbatLogic::AST* __2860403603 = pExpression;
		pExpression = 0;
		pDisownExpr->AddChild(__2860403603);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::DisownExpr* __1761905829 = pDisownExpr;
		pDisownExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
		return __1761905829;
	}

	void DisownExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		if (m_pExpression->m_pValueType == 0)
		{
			pValidator->AddError("No valuetype for expression???", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
		if (m_pExpression->m_pValueType->m_eType != ValueType::Type::CLASS_DECL_VALUE && m_pExpression->m_pValueType->m_eType != ValueType::Type::GENERIC_TYPE_DECL_VALUE)
		{
			pValidator->AddError("Expected right side of Disown to be a CLASS_DECL_VALUE or GENERIC_TYPE_DECL_VALUE", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
		if (m_pExpression->m_pValueType->m_ePointerType != TypeRef::PointerType::OWNED)
		{
			pValidator->AddError("Expected right side of Disown to be a OWNED type", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
		m_pValueType = m_pExpression->m_pValueType->Clone();
		m_pValueType->m_ePointerType = TypeRef::PointerType::TRANSITON;
		if (m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
		{
			if (m_pValueType->m_pClassDecl == 0)
			{
				pValidator->AddError("Can't disown unbeknownst thing (ClassDecl)", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
				return;
			}
		}
		else
			if (m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
			{
				if (m_pValueType->m_pGenericTypeDecl == 0)
				{
					pValidator->AddError("Can't disown unbeknownst thing (GenericTypeDecl)", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
					return;
				}
			}
		AST* pParentStatement = GetParentStatement();
		if (pParentStatement == 0)
		{
			pValidator->AddError("Can'd find disown parent???", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
		InternalString* sTempName = new InternalString("");
		m_pExpression->Stringify(AST::Language::CPP, AST::OutputFile::SOURCE, 0, sTempName);
		sTempName->AppendInt(pParentStatement->m_pFirstToken->m_nLine);
		unsigned int nHash = Util::BadHash(sTempName);
		sTempName->Set("__");
		sTempName->AppendUint32(nHash);
		AST* pParentParent = pParentStatement->m_pParent;
		{
			TypeRef* pTypeRef = m_pValueType->CreateTypeRef();
			Token* pNameToken = new Token();
			pNameToken->m_eType = Token::Type::TOKEN_IDENTIFIER;
			pNameToken->m_sValue = new InternalString(sTempName->GetExternalString());
			AST* pAssignment = m_pExpression->BaseClone();
			VarDecl* pTempVarDecl = new VarDecl();
			pTempVarDecl->m_pFirstToken = pTypeRef->m_pFirstToken;
			pTempVarDecl->m_pTypeRef = pTypeRef;
			pTempVarDecl->m_pNameToken = pNameToken;
			NumbatLogic::Token* __2203125382 = pNameToken;
			pNameToken = 0;
			pTempVarDecl->m_pOwnedNameToken = __2203125382;
			pTempVarDecl->m_pAssignment = pAssignment;
			NumbatLogic::TypeRef* __4074434202 = pTypeRef;
			pTypeRef = 0;
			pTempVarDecl->AddChild(__4074434202);
			NumbatLogic::AST* __2104814021 = pAssignment;
			pAssignment = 0;
			pTempVarDecl->AddChild(__2104814021);
			NumbatLogic::VarDecl* __515626666 = pTempVarDecl;
			pTempVarDecl = 0;
			pParentParent->AddChildBefore(__515626666, pParentStatement);
			if (pTypeRef) delete pTypeRef;
			if (pNameToken) delete pNameToken;
			if (pAssignment) delete pAssignment;
			if (pTempVarDecl) delete pTempVarDecl;
		}
		{
			AST* pLeft = m_pExpression->BaseClone();
			NullExpr* pRight = new NullExpr();
			Token* pOperatorToken = new Token();
			pOperatorToken->m_eType = Token::Type::TOKEN_EQUALS;
			OperatorExpr* pOperatorExpr = new OperatorExpr();
			pOperatorExpr->m_eType = AST::Type::AST_OPERATOR_EXPR;
			pOperatorExpr->m_pFirstToken = pLeft->m_pFirstToken;
			pOperatorExpr->m_pOperatorToken = pOperatorToken;
			NumbatLogic::Token* __320250430 = pOperatorToken;
			pOperatorToken = 0;
			pOperatorExpr->m_pOwnedOperatorToken = __320250430;
			pOperatorExpr->m_pLeft = pLeft;
			pOperatorExpr->m_pRight = pRight;
			NumbatLogic::AST* __3234717067 = pLeft;
			pLeft = 0;
			pOperatorExpr->AddChild(__3234717067);
			NumbatLogic::NullExpr* __3282956112 = pRight;
			pRight = 0;
			pOperatorExpr->AddChild(__3282956112);
			ExpressionStmt* pExpressionStmt = new ExpressionStmt();
			pExpressionStmt->m_pFirstToken = pOperatorExpr->m_pFirstToken;
			pExpressionStmt->m_pExpression = pOperatorExpr;
			NumbatLogic::OperatorExpr* __2372259848 = pOperatorExpr;
			pOperatorExpr = 0;
			pExpressionStmt->AddChild(__2372259848);
			NumbatLogic::ExpressionStmt* __882741888 = pExpressionStmt;
			pExpressionStmt = 0;
			pParentParent->AddChildBefore(__882741888, pParentStatement);
			if (pLeft) delete pLeft;
			if (pRight) delete pRight;
			if (pOperatorToken) delete pOperatorToken;
			if (pOperatorExpr) delete pOperatorExpr;
			if (pExpressionStmt) delete pExpressionStmt;
		}
		NumbatLogic::InternalString* __2418846473 = sTempName;
		sTempName = 0;
		m_sTempVarName = __2418846473;
		if (sTempName) delete sTempName;
	}

	void DisownExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (m_sTempVarName != 0)
		{
			sOut->Append(m_sTempVarName->GetExternalString());
			return;
		}
		if (eLanguage == AST::Language::NLL)
		{
			sOut->Append("disown ");
		}
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
	}

	DisownExpr::~DisownExpr()
	{
		if (m_sTempVarName) delete m_sTempVarName;
	}

}

