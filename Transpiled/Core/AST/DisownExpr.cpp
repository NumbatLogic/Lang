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
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
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
	class OutputBuilder;
	class ExternalString;
	class TypeRef;
	class VarDecl;
	class NullExpr;
	class OperatorExpr;
	class ExpressionStmt;
}
#line 0 "../../../Source/Core/AST/DisownExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/DisownExpr.nll"
#line 8 "../../../Source/Core/AST/DisownExpr.nll"
	DisownExpr::DisownExpr()
	{
		m_pExpression = 0;
		m_sTempVarName = 0;
#line 10 "../../../Source/Core/AST/DisownExpr.nll"
		m_eType = AST::Type::AST_DISOWN_EXP;
	}

	DisownExpr* DisownExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/DisownExpr.nll"
		Token* pDisownToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DISOWN);
		if (pDisownToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 19 "../../../Source/Core/AST/DisownExpr.nll"
			return 0;
		}
#line 20 "../../../Source/Core/AST/DisownExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 22 "../../../Source/Core/AST/DisownExpr.nll"
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
		if (pExpression == 0)
		{
			Console::Log("expected expresssion");
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 27 "../../../Source/Core/AST/DisownExpr.nll"
			return 0;
		}
#line 30 "../../../Source/Core/AST/DisownExpr.nll"
		DisownExpr* pDisownExpr = new DisownExpr();
#line 32 "../../../Source/Core/AST/DisownExpr.nll"
		pDisownExpr->m_pFirstToken = pDisownToken;
		pDisownExpr->m_pExpression = pExpression;
		NumbatLogic::AST* __1929399913 = pExpression;
#line 34 "../../../Source/Core/AST/DisownExpr.nll"
		pExpression = 0;
#line 34 "../../../Source/Core/AST/DisownExpr.nll"
		pDisownExpr->AddChild(__1929399913);
#line 36 "../../../Source/Core/AST/DisownExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::DisownExpr* __1970191169 = pDisownExpr;
#line 37 "../../../Source/Core/AST/DisownExpr.nll"
		pDisownExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 37 "../../../Source/Core/AST/DisownExpr.nll"
		return __1970191169;
	}

	void DisownExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
#line 44 "../../../Source/Core/AST/DisownExpr.nll"
		if (m_pExpression->m_pValueType == 0)
		{
			pValidator->AddError("No valuetype for expression???", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
#line 50 "../../../Source/Core/AST/DisownExpr.nll"
		if (m_pExpression->m_pValueType->m_eType != ValueType::Type::CLASS_DECL_VALUE && m_pExpression->m_pValueType->m_eType != ValueType::Type::GENERIC_TYPE_DECL_VALUE)
		{
			pValidator->AddError("Expected right side of Disown to be a CLASS_DECL_VALUE or GENERIC_TYPE_DECL_VALUE", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
#line 56 "../../../Source/Core/AST/DisownExpr.nll"
		if (m_pExpression->m_pValueType->m_ePointerType != TypeRef::PointerType::OWNED)
		{
			pValidator->AddError("Expected right side of Disown to be a OWNED type", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
#line 62 "../../../Source/Core/AST/DisownExpr.nll"
		m_pValueType = m_pExpression->m_pValueType->Clone();
		m_pValueType->m_ePointerType = TypeRef::PointerType::TRANSITON;
#line 66 "../../../Source/Core/AST/DisownExpr.nll"
		if (m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
		{
			if (m_pValueType->m_pClassDecl == 0)
			{
				pValidator->AddError("Can't disown unbeknownst thing (ClassDecl)", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
				return;
			}
		}
		else
#line 74 "../../../Source/Core/AST/DisownExpr.nll"
			if (m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
			{
				if (m_pValueType->m_pGenericTypeDecl == 0)
				{
					pValidator->AddError("Can't disown unbeknownst thing (GenericTypeDecl)", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
					return;
				}
			}
#line 83 "../../../Source/Core/AST/DisownExpr.nll"
		AST* pParentStatement = GetParentStatement();
		if (pParentStatement == 0)
		{
			pValidator->AddError("Can'd find disown parent???", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
			return;
		}
#line 90 "../../../Source/Core/AST/DisownExpr.nll"
		InternalString* sTempName = new InternalString("");
		OutputBuilder* outTemp = new OutputBuilder();
		m_pExpression->Stringify(AST::Language::CPP, AST::OutputFile::SOURCE, 0, outTemp);
#line 94 "../../../Source/Core/AST/DisownExpr.nll"
		sTempName->Append(outTemp->m_sOut->GetExternalString());
#line 96 "../../../Source/Core/AST/DisownExpr.nll"
		sTempName->AppendInt(pParentStatement->m_pFirstToken->m_nLine);
		unsigned int nHash = ExternalString::GetChecksum(sTempName->GetExternalString());
#line 99 "../../../Source/Core/AST/DisownExpr.nll"
		sTempName->Set("__");
		sTempName->AppendUint32(nHash);
#line 105 "../../../Source/Core/AST/DisownExpr.nll"
		AST* pParentParent = pParentStatement->m_pParent;
		{
#line 108 "../../../Source/Core/AST/DisownExpr.nll"
			TypeRef* pTypeRef = m_pValueType->CreateTypeRef();
			Token* pNameToken = new Token();
			pNameToken->m_eType = Token::Type::TOKEN_IDENTIFIER;
			pNameToken->m_sValue = new InternalString(sTempName->GetExternalString());
#line 115 "../../../Source/Core/AST/DisownExpr.nll"
			AST* pAssignment = m_pExpression->BaseClone();
#line 117 "../../../Source/Core/AST/DisownExpr.nll"
			VarDecl* pTempVarDecl = new VarDecl();
			pTempVarDecl->m_pFirstToken = pTypeRef->m_pFirstToken;
			pTempVarDecl->m_pTypeRef = pTypeRef;
			pTempVarDecl->m_pNameToken = pNameToken;
			NumbatLogic::Token* __2859238226 = pNameToken;
#line 121 "../../../Source/Core/AST/DisownExpr.nll"
			pNameToken = 0;
#line 121 "../../../Source/Core/AST/DisownExpr.nll"
			pTempVarDecl->m_pOwnedNameToken = __2859238226;
			pTempVarDecl->m_pAssignment = pAssignment;
			NumbatLogic::TypeRef* __967647721 = pTypeRef;
#line 123 "../../../Source/Core/AST/DisownExpr.nll"
			pTypeRef = 0;
#line 123 "../../../Source/Core/AST/DisownExpr.nll"
			pTempVarDecl->AddChild(__967647721);
			NumbatLogic::AST* __183884758 = pAssignment;
#line 124 "../../../Source/Core/AST/DisownExpr.nll"
			pAssignment = 0;
#line 124 "../../../Source/Core/AST/DisownExpr.nll"
			pTempVarDecl->AddChild(__183884758);
#line 126 "../../../Source/Core/AST/DisownExpr.nll"
			AST* pInjectedVarDecl = pTempVarDecl;
			NumbatLogic::VarDecl* __3774795561 = pTempVarDecl;
#line 127 "../../../Source/Core/AST/DisownExpr.nll"
			pTempVarDecl = 0;
#line 127 "../../../Source/Core/AST/DisownExpr.nll"
			pParentParent->AddChildBefore(__3774795561, pParentStatement);
			pValidator->ValidateSubtree(pInjectedVarDecl);
			if (pTypeRef) delete pTypeRef;
			if (pNameToken) delete pNameToken;
			if (pAssignment) delete pAssignment;
			if (pTempVarDecl) delete pTempVarDecl;
		}
		{
#line 132 "../../../Source/Core/AST/DisownExpr.nll"
			AST* pLeft = m_pExpression->BaseClone();
#line 134 "../../../Source/Core/AST/DisownExpr.nll"
			NullExpr* pRight = new NullExpr();
#line 136 "../../../Source/Core/AST/DisownExpr.nll"
			Token* pOperatorToken = new Token();
			pOperatorToken->m_eType = Token::Type::TOKEN_EQUALS;
			NumbatLogic::AST* __3919013152 = pLeft;
			pLeft = 0;
			NumbatLogic::NullExpr* __534132299 = pRight;
#line 139 "../../../Source/Core/AST/DisownExpr.nll"
			pRight = 0;
#line 139 "../../../Source/Core/AST/DisownExpr.nll"
			OperatorExpr* pOperatorExpr = OperatorExpr::Create(OperatorExpr::OperatorType::ASSIGNMENT, pOperatorToken, __3919013152, __534132299);
			NumbatLogic::Token* __3603785160 = pOperatorToken;
#line 140 "../../../Source/Core/AST/DisownExpr.nll"
			pOperatorToken = 0;
#line 140 "../../../Source/Core/AST/DisownExpr.nll"
			pOperatorExpr->m_pOwnedOperatorToken = __3603785160;
#line 142 "../../../Source/Core/AST/DisownExpr.nll"
			ExpressionStmt* pExpressionStmt = new ExpressionStmt();
			pExpressionStmt->m_pFirstToken = pOperatorExpr->m_pFirstToken;
			pExpressionStmt->m_pExpression = pOperatorExpr;
			NumbatLogic::OperatorExpr* __2365778377 = pOperatorExpr;
#line 145 "../../../Source/Core/AST/DisownExpr.nll"
			pOperatorExpr = 0;
#line 145 "../../../Source/Core/AST/DisownExpr.nll"
			pExpressionStmt->AddChild(__2365778377);
#line 147 "../../../Source/Core/AST/DisownExpr.nll"
			AST* pInjectedStmt = pExpressionStmt;
			NumbatLogic::ExpressionStmt* __1415267173 = pExpressionStmt;
#line 148 "../../../Source/Core/AST/DisownExpr.nll"
			pExpressionStmt = 0;
#line 148 "../../../Source/Core/AST/DisownExpr.nll"
			pParentParent->AddChildBefore(__1415267173, pParentStatement);
			pValidator->ValidateSubtree(pInjectedStmt);
			if (pLeft) delete pLeft;
			if (pRight) delete pRight;
			if (pOperatorToken) delete pOperatorToken;
			if (pOperatorExpr) delete pOperatorExpr;
			if (pExpressionStmt) delete pExpressionStmt;
		}
		NumbatLogic::InternalString* __3313827548 = sTempName;
#line 152 "../../../Source/Core/AST/DisownExpr.nll"
		sTempName = 0;
#line 152 "../../../Source/Core/AST/DisownExpr.nll"
		m_sTempVarName = __3313827548;
		if (sTempName) delete sTempName;
		if (outTemp) delete outTemp;
	}

#line 155 "../../../Source/Core/AST/DisownExpr.nll"
	void DisownExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (m_sTempVarName != 0)
		{
			pOutputBuilder->m_sOut->Append(m_sTempVarName->GetExternalString());
			return;
		}
#line 163 "../../../Source/Core/AST/DisownExpr.nll"
		if (eLanguage == AST::Language::NLL)
		{
			pOutputBuilder->m_sOut->Append("disown ");
		}
#line 168 "../../../Source/Core/AST/DisownExpr.nll"
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

#line 3 "../../../Source/Core/AST/DisownExpr.nll"
	DisownExpr::~DisownExpr()
	{
		if (m_sTempVarName) delete m_sTempVarName;
	}

}

