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
#line 1 "../../../Source/Core/AST/DisownExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/DisownExpr.nll"
#line 9 "../../../Source/Core/AST/DisownExpr.nll"
	DisownExpr::DisownExpr()
	{
		m_pExpression = 0;
		m_sTempVarName = 0;
#line 11 "../../../Source/Core/AST/DisownExpr.nll"
		m_eType = AST::Type::AST_DISOWN_EXP;
	}

#line 14 "../../../Source/Core/AST/DisownExpr.nll"
	DisownExpr* DisownExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pDisownToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DISOWN);
#line 19 "../../../Source/Core/AST/DisownExpr.nll"
		if (pDisownToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 20 "../../../Source/Core/AST/DisownExpr.nll"
			return 0;
		}
#line 21 "../../../Source/Core/AST/DisownExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 24 "../../../Source/Core/AST/DisownExpr.nll"
		if (pExpression == 0)
		{
#line 26 "../../../Source/Core/AST/DisownExpr.nll"
			Console::Log("expected expresssion");
#line 27 "../../../Source/Core/AST/DisownExpr.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pExpression) delete pExpression;
#line 28 "../../../Source/Core/AST/DisownExpr.nll"
			return 0;
		}
		DisownExpr* pDisownExpr = new DisownExpr();
#line 33 "../../../Source/Core/AST/DisownExpr.nll"
		pDisownExpr->m_pFirstToken = pDisownToken;
#line 34 "../../../Source/Core/AST/DisownExpr.nll"
		pDisownExpr->m_pExpression = pExpression;
		NumbatLogic::AST* __1929399913 = pExpression;
#line 35 "../../../Source/Core/AST/DisownExpr.nll"
		pExpression = 0;
#line 35 "../../../Source/Core/AST/DisownExpr.nll"
		pDisownExpr->AddChild(__1929399913);
#line 37 "../../../Source/Core/AST/DisownExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::DisownExpr* __1970191169 = pDisownExpr;
#line 38 "../../../Source/Core/AST/DisownExpr.nll"
		pDisownExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pExpression) delete pExpression;
#line 38 "../../../Source/Core/AST/DisownExpr.nll"
		return __1970191169;
	}

#line 41 "../../../Source/Core/AST/DisownExpr.nll"
	void DisownExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 43 "../../../Source/Core/AST/DisownExpr.nll"
		AST::Validate(pValidator, pParent);
#line 45 "../../../Source/Core/AST/DisownExpr.nll"
		if (m_pExpression->m_pValueType == 0)
		{
#line 47 "../../../Source/Core/AST/DisownExpr.nll"
			pValidator->AddError("No valuetype for expression???", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
#line 48 "../../../Source/Core/AST/DisownExpr.nll"
			return;
		}
#line 51 "../../../Source/Core/AST/DisownExpr.nll"
		if (m_pExpression->m_pValueType->m_eType != ValueType::Type::CLASS_DECL_VALUE && m_pExpression->m_pValueType->m_eType != ValueType::Type::GENERIC_TYPE_DECL_VALUE)
		{
#line 53 "../../../Source/Core/AST/DisownExpr.nll"
			pValidator->AddError("Expected right side of Disown to be a CLASS_DECL_VALUE or GENERIC_TYPE_DECL_VALUE", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
#line 54 "../../../Source/Core/AST/DisownExpr.nll"
			return;
		}
#line 57 "../../../Source/Core/AST/DisownExpr.nll"
		if (m_pExpression->m_pValueType->m_ePointerType != TypeRef::PointerType::OWNED)
		{
#line 59 "../../../Source/Core/AST/DisownExpr.nll"
			pValidator->AddError("Expected right side of Disown to be a OWNED type", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
#line 60 "../../../Source/Core/AST/DisownExpr.nll"
			return;
		}
#line 63 "../../../Source/Core/AST/DisownExpr.nll"
		m_pValueType = m_pExpression->m_pValueType->Clone();
#line 64 "../../../Source/Core/AST/DisownExpr.nll"
		m_pValueType->m_ePointerType = TypeRef::PointerType::TRANSITON;
#line 67 "../../../Source/Core/AST/DisownExpr.nll"
		if (m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
		{
#line 69 "../../../Source/Core/AST/DisownExpr.nll"
			if (m_pValueType->m_pClassDecl == 0)
			{
#line 71 "../../../Source/Core/AST/DisownExpr.nll"
				pValidator->AddError("Can't disown unbeknownst thing (ClassDecl)", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
#line 72 "../../../Source/Core/AST/DisownExpr.nll"
				return;
			}
		}
		else
#line 75 "../../../Source/Core/AST/DisownExpr.nll"
			if (m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
			{
#line 77 "../../../Source/Core/AST/DisownExpr.nll"
				if (m_pValueType->m_pGenericTypeDecl == 0)
				{
#line 79 "../../../Source/Core/AST/DisownExpr.nll"
					pValidator->AddError("Can't disown unbeknownst thing (GenericTypeDecl)", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
#line 80 "../../../Source/Core/AST/DisownExpr.nll"
					return;
				}
			}
		AST* pParentStatement = GetParentStatement();
#line 85 "../../../Source/Core/AST/DisownExpr.nll"
		if (pParentStatement == 0)
		{
#line 87 "../../../Source/Core/AST/DisownExpr.nll"
			pValidator->AddError("Can'd find disown parent???", m_pExpression->m_pFirstToken->m_sFileName, m_pExpression->m_pFirstToken->m_nLine, m_pExpression->m_pFirstToken->m_nColumn);
#line 88 "../../../Source/Core/AST/DisownExpr.nll"
			return;
		}
		InternalString* sTempName = new InternalString("");
		OutputBuilder* outTemp = new OutputBuilder();
#line 93 "../../../Source/Core/AST/DisownExpr.nll"
		m_pExpression->Stringify(AST::Language::CPP, AST::OutputFile::SOURCE, 0, outTemp);
#line 95 "../../../Source/Core/AST/DisownExpr.nll"
		sTempName->Append(outTemp->m_sOut->GetExternalString());
#line 97 "../../../Source/Core/AST/DisownExpr.nll"
		sTempName->AppendInt(pParentStatement->m_pFirstToken->m_nLine);
		unsigned int nHash = ExternalString::GetChecksum(sTempName->GetExternalString());
#line 100 "../../../Source/Core/AST/DisownExpr.nll"
		sTempName->Set("__");
#line 101 "../../../Source/Core/AST/DisownExpr.nll"
		sTempName->AppendUint32(nHash);
		AST* pParentParent = pParentStatement->m_pParent;
		{
			TypeRef* pTypeRef = m_pValueType->CreateTypeRef();
			Token* pNameToken = new Token();
#line 111 "../../../Source/Core/AST/DisownExpr.nll"
			pNameToken->m_eType = Token::Type::TOKEN_IDENTIFIER;
#line 112 "../../../Source/Core/AST/DisownExpr.nll"
			pNameToken->m_sValue = new InternalString(sTempName->GetExternalString());
			AST* pAssignment = m_pExpression->BaseClone();
			VarDecl* pTempVarDecl = new VarDecl();
#line 119 "../../../Source/Core/AST/DisownExpr.nll"
			pTempVarDecl->m_pFirstToken = pTypeRef->m_pFirstToken;
#line 120 "../../../Source/Core/AST/DisownExpr.nll"
			pTempVarDecl->m_pTypeRef = pTypeRef;
#line 121 "../../../Source/Core/AST/DisownExpr.nll"
			pTempVarDecl->m_pNameToken = pNameToken;
			NumbatLogic::Token* __2859238226 = pNameToken;
#line 122 "../../../Source/Core/AST/DisownExpr.nll"
			pNameToken = 0;
#line 122 "../../../Source/Core/AST/DisownExpr.nll"
			pTempVarDecl->m_pOwnedNameToken = __2859238226;
#line 123 "../../../Source/Core/AST/DisownExpr.nll"
			pTempVarDecl->m_pAssignment = pAssignment;
			NumbatLogic::TypeRef* __967647721 = pTypeRef;
#line 124 "../../../Source/Core/AST/DisownExpr.nll"
			pTypeRef = 0;
#line 124 "../../../Source/Core/AST/DisownExpr.nll"
			pTempVarDecl->AddChild(__967647721);
			NumbatLogic::AST* __183884758 = pAssignment;
#line 125 "../../../Source/Core/AST/DisownExpr.nll"
			pAssignment = 0;
#line 125 "../../../Source/Core/AST/DisownExpr.nll"
			pTempVarDecl->AddChild(__183884758);
			AST* pInjectedVarDecl = pTempVarDecl;
			NumbatLogic::VarDecl* __3774795561 = pTempVarDecl;
#line 128 "../../../Source/Core/AST/DisownExpr.nll"
			pTempVarDecl = 0;
#line 128 "../../../Source/Core/AST/DisownExpr.nll"
			pParentParent->AddChildBefore(__3774795561, pParentStatement);
#line 129 "../../../Source/Core/AST/DisownExpr.nll"
			pValidator->ValidateSubtree(pInjectedVarDecl);
			if (pTypeRef) delete pTypeRef;
			if (pNameToken) delete pNameToken;
			if (pAssignment) delete pAssignment;
			if (pTempVarDecl) delete pTempVarDecl;
		}
		{
			AST* pLeft = m_pExpression->BaseClone();
			NullExpr* pRight = new NullExpr();
			Token* pOperatorToken = new Token();
#line 138 "../../../Source/Core/AST/DisownExpr.nll"
			pOperatorToken->m_eType = Token::Type::TOKEN_EQUALS;
			NumbatLogic::AST* __3919013152 = pLeft;
#line 140 "../../../Source/Core/AST/DisownExpr.nll"
			pLeft = 0;
			NumbatLogic::NullExpr* __534132299 = pRight;
#line 140 "../../../Source/Core/AST/DisownExpr.nll"
			pRight = 0;
			OperatorExpr* pOperatorExpr = OperatorExpr::Create(OperatorExpr::OperatorType::ASSIGNMENT, pOperatorToken, __3919013152, __534132299);
			NumbatLogic::Token* __3603785160 = pOperatorToken;
#line 141 "../../../Source/Core/AST/DisownExpr.nll"
			pOperatorToken = 0;
#line 141 "../../../Source/Core/AST/DisownExpr.nll"
			pOperatorExpr->m_pOwnedOperatorToken = __3603785160;
			ExpressionStmt* pExpressionStmt = new ExpressionStmt();
#line 144 "../../../Source/Core/AST/DisownExpr.nll"
			pExpressionStmt->m_pFirstToken = pOperatorExpr->m_pFirstToken;
#line 145 "../../../Source/Core/AST/DisownExpr.nll"
			pExpressionStmt->m_pExpression = pOperatorExpr;
			NumbatLogic::OperatorExpr* __2365778377 = pOperatorExpr;
#line 146 "../../../Source/Core/AST/DisownExpr.nll"
			pOperatorExpr = 0;
#line 146 "../../../Source/Core/AST/DisownExpr.nll"
			pExpressionStmt->AddChild(__2365778377);
			AST* pInjectedStmt = pExpressionStmt;
			NumbatLogic::ExpressionStmt* __1415267173 = pExpressionStmt;
#line 149 "../../../Source/Core/AST/DisownExpr.nll"
			pExpressionStmt = 0;
#line 149 "../../../Source/Core/AST/DisownExpr.nll"
			pParentParent->AddChildBefore(__1415267173, pParentStatement);
#line 150 "../../../Source/Core/AST/DisownExpr.nll"
			pValidator->ValidateSubtree(pInjectedStmt);
			if (pLeft) delete pLeft;
			if (pRight) delete pRight;
			if (pOperatorToken) delete pOperatorToken;
			if (pOperatorExpr) delete pOperatorExpr;
			if (pExpressionStmt) delete pExpressionStmt;
		}
		NumbatLogic::InternalString* __3313827548 = sTempName;
#line 153 "../../../Source/Core/AST/DisownExpr.nll"
		sTempName = 0;
#line 153 "../../../Source/Core/AST/DisownExpr.nll"
		m_sTempVarName = __3313827548;
		if (sTempName) delete sTempName;
		if (outTemp) delete outTemp;
	}

#line 156 "../../../Source/Core/AST/DisownExpr.nll"
	void DisownExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 158 "../../../Source/Core/AST/DisownExpr.nll"
		if (m_sTempVarName != 0)
		{
#line 160 "../../../Source/Core/AST/DisownExpr.nll"
			pOutputBuilder->m_sOut->Append(m_sTempVarName->GetExternalString());
#line 161 "../../../Source/Core/AST/DisownExpr.nll"
			return;
		}
#line 164 "../../../Source/Core/AST/DisownExpr.nll"
		if (eLanguage == AST::Language::NLL)
		{
#line 166 "../../../Source/Core/AST/DisownExpr.nll"
			pOutputBuilder->m_sOut->Append("disown ");
		}
#line 169 "../../../Source/Core/AST/DisownExpr.nll"
		m_pExpression->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

#line 4 "../../../Source/Core/AST/DisownExpr.nll"
	DisownExpr::~DisownExpr()
	{
		if (m_sTempVarName) delete m_sTempVarName;
	}

}

