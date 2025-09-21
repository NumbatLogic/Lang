#include "Identifier.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "OperatorExpr.hpp"
#include "../ValueType.hpp"
#include "ClassDecl.hpp"
#include "EnumDecl.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../NamespaceNode.hpp"
#include "NamespaceDecl.hpp"
#include "../Validator.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "VarDecl.hpp"
#include "MemberVarDecl.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Identifier;
	class AST;
	class OperatorExpr;
	template <class T>
	class Vector;
	class NamespaceDecl;
	class NamespaceNode;
	class Validator;
	class InternalString;
	class ClassDecl;
	class VarDecl;
	class MemberVarDecl;
	class EnumDecl;
	class EnumDeclValue;
	class TypeRef;
	template <class T>
	class OwnedVector;
	class ValueType;
	class FunctionDecl;
}
namespace NumbatLogic
{
	Identifier* Identifier::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		Identifier* pIdentifier = new Identifier();
		pIdentifier->m_eType = AST::Type::AST_IDENTIFIER;
		pIdentifier->m_pFirstToken = pToken;
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::Identifier* __3348370355 = pIdentifier;
		pIdentifier = 0;
		if (pTempOffset) delete pTempOffset;
		return __3348370355;
	}

	AST* Identifier::BaseClone()
	{
		Identifier* pIdentifier = new Identifier();
		pIdentifier->m_eType = m_eType;
		pIdentifier->m_pFirstToken = m_pFirstToken;
		NumbatLogic::Identifier* __3432266336 = pIdentifier;
		pIdentifier = 0;
		return __3432266336;
	}

	void Identifier::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		const char* sName = m_pFirstToken->GetString();
		AST* pAST = 0;
		AST* pBase = this;
		AST* pChild = this;
		if (pParent != 0)
		{
			if (pParent->m_pOperatorToken->m_eType == Token::Type::TOKEN_DOT && pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
			{
				AddClassDeclReference(pParent->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
				pBase = pParent->m_pLeft->m_pValueType->m_pClassDecl;
				pChild = 0;
			}
			else
				if (pParent->m_pOperatorToken->m_eType == Token::Type::TOKEN_DOUBLE_COLON)
				{
					if (pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL)
					{
						AddClassDeclReference(pParent->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
						pBase = pParent->m_pLeft->m_pValueType->m_pClassDecl;
						pChild = 0;
					}
					else
						if (pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL)
						{
							pBase = pParent->m_pLeft->m_pValueType->m_pEnumDecl;
							pChild = 0;
						}
						else
							if (pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::NAMESPACE_NODE)
							{
								Vector<NamespaceDecl*>* pNamespaceDeclVector = pParent->m_pLeft->m_pValueType->m_pNamespaceNode->m_pNamespaceDeclVector;
								for (int i = 0; i < pNamespaceDeclVector->GetSize(); i++)
								{
									NamespaceDecl* pNamespaceDecl = pNamespaceDeclVector->Get(i);
									pAST = pNamespaceDecl->FindByName(sName, 0);
									if (pAST != 0)
										break;
								}
							}
							else
							{
								pValidator->AddError("Unexpected left of ::", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
								return;
							}
				}
		}
		if (pAST == 0)
			pAST = pBase->FindByName(sName, pChild);
		if (pAST == 0)
		{
			InternalString* sTemp = new InternalString("Identifier Unbeknownst! ");
			sTemp->Append(sName);
			if (pParent != 0)
				sTemp->Append(" has parent");
			sTemp->Append(" base: ");
			pBase->StringifyType(sTemp);
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
			return;
		}
		if (pAST->m_eType == AST::Type::AST_CLASS_DECL)
		{
			m_pValueType = new ValueType(ValueType::Type::CLASS_DECL);
			m_pValueType->m_pClassDecl = (ClassDecl*)(pAST);
			AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
			AST* pCheckParent = m_pParent;
			AST* pCurrent = this;
			for (int i = 0; i < 5; i++)
			{
				if (pCheckParent == 0)
					break;
				if (pCheckParent->m_eType == AST::Type::AST_VAR_DECL)
				{
					VarDecl* pVarDecl = (VarDecl*)(pCheckParent);
					if (pCurrent == pVarDecl->m_pArraySize && pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
						AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::HEADER, false);
					if (pCurrent == pVarDecl->m_pAssignment && pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
					{
						MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pVarDecl->m_pParent);
						if (pMemberVarDecl->m_bStatic)
							AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::HEADER, false);
					}
					break;
				}
				pCurrent = pCheckParent;
				pCheckParent = pCheckParent->m_pParent;
			}
			return;
		}
		if (pAST->m_eType == AST::Type::AST_ENUM_DECL)
		{
			m_pValueType = new ValueType(ValueType::Type::ENUM_DECL);
			m_pValueType->m_pEnumDecl = (EnumDecl*)(pAST);
			return;
		}
		if (pAST->m_eType == AST::Type::ENUM_DECL_VALUE)
		{
			m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
			m_pValueType->m_pEnumDeclValue = (EnumDeclValue*)(pAST);
			return;
		}
		if (pAST->m_eType == AST::Type::AST_VAR_DECL)
		{
			VarDecl* pVarDecl = (VarDecl*)(pAST);
			m_pValueType = pVarDecl->m_pTypeRef->CreateValueType();
			if (m_pValueType == 0)
			{
				pValidator->AddError("Could not create ValueType for VarDecl", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				return;
			}
			if (m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
			{
				if (pParent != 0)
				{
					if (pParent->m_pOperatorToken->m_eType == Token::Type::TOKEN_DOT && pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
					{
						if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector != 0)
						{
							if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->GetSize() > 0)
							{
								ValueType* pGenericValueType = pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->Get(0);
								if (pGenericValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
								{
									ValueType* pOldValueType = 0;
									NumbatLogic::ValueType* __1479815806 = m_pValueType;
									m_pValueType = 0;
									pOldValueType = __1479815806;
									m_pValueType = pGenericValueType->Clone();
									m_pValueType->m_ePointerType = pOldValueType->m_ePointerType;
									if (pOldValueType) delete pOldValueType;
								}
							}
						}
					}
				}
			}
			return;
		}
		if (pAST->m_eType == AST::Type::AST_FUNCTION_DECL)
		{
			m_pValueType = new ValueType(ValueType::Type::FUNCTION_DECL);
			m_pValueType->m_pFunctionDecl = (FunctionDecl*)(pAST);
			return;
		}
		if (pAST->m_eType == AST::Type::NAMESPACE_DECL)
		{
			m_pValueType = new ValueType(ValueType::Type::NAMESPACE_NODE);
			m_pValueType->m_pNamespaceNode = ((NamespaceDecl*)(pAST))->m_pNamespaceNode;
			return;
		}
		{
			InternalString* sTemp = new InternalString("say what? ");
			pAST->StringifyType(sTemp);
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
		}
		AST::Validate(pValidator, pParent);
	}

	void Identifier::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		m_pFirstToken->Stringify(sOut);
	}

}

