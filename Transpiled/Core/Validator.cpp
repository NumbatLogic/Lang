#include "Validator.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "AST/VarDecl.hpp"
#include "../../../LangShared/Vector/CPP/Vector.hpp"
#include "AST/Scope.hpp"
#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "Project.hpp"
#include "Semantic/Resolver.hpp"
#include "AST/AST.hpp"
#include "NamespaceNode.hpp"
#include "AST/TranslationUnit.hpp"
#include "../../../LangShared/Console/CPP/Console.hpp"
#include "AST/TypeRef.hpp"
#include "ValueType.hpp"
#include "../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST/VarDeclDescope.hpp"
#include "AST/ReturnStmt.hpp"
#include "AST/DisownExpr.hpp"
#include "../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "Token.hpp"
#include "AST/Identifier.hpp"

namespace NumbatLogic
{
	class VarDecl;
	template <class T>
	class Vector;
	class Scope;
	class Validator;
	class ValidatorError;
	template <class T>
	class OwnedVector;
	class ValidatorScope;
	class Project;
	class Resolver;
	class AST;
	class NamespaceDecl;
	class NamespaceNode;
	class InternalString;
	class TranslationUnit;
	class Console;
	class ValueType;
	class TypeRef;
	class Assert;
	class VarDeclDescope;
	class Identifier;
	class ReturnStmt;
	class DisownExpr;
	class ExternalString;
	class Token;
}
#line 0 "../../../Source/Core/Validator.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Validator.nll"
#line 3 "../../../Source/Core/Validator.nll"
	ValidatorError::ValidatorError()
	{
		m_sError = 0;
		m_sFile = 0;
		m_nLine = 0;
		m_nColumn = 0;
	}

#line 3 "../../../Source/Core/Validator.nll"
	ValidatorError::~ValidatorError()
	{
		if (m_sError) delete m_sError;
		if (m_sFile) delete m_sFile;
	}

#line 11 "../../../Source/Core/Validator.nll"
#line 16 "../../../Source/Core/Validator.nll"
	ValidatorScope::ValidatorScope(Scope* pScope)
	{
		m_pScope = 0;
		m_pVarDeclVector = 0;
#line 18 "../../../Source/Core/Validator.nll"
		m_pScope = pScope;
#line 19 "../../../Source/Core/Validator.nll"
		m_pVarDeclVector = new Vector<VarDecl*>();
	}

#line 11 "../../../Source/Core/Validator.nll"
	ValidatorScope::~ValidatorScope()
	{
		if (m_pVarDeclVector) delete m_pVarDeclVector;
	}

#line 23 "../../../Source/Core/Validator.nll"
#line 34 "../../../Source/Core/Validator.nll"
	Validator::Validator(Project* pProject)
	{
		m_pProject = 0;
		m_pValidatorErrorVector = 0;
		m_pValidatorScopeVector = 0;
		m_pCurrentNamespaceNode = 0;
		m_pResolver = 0;
#line 36 "../../../Source/Core/Validator.nll"
		m_pProject = pProject;
#line 37 "../../../Source/Core/Validator.nll"
		m_pValidatorErrorVector = new OwnedVector<ValidatorError*>();
#line 38 "../../../Source/Core/Validator.nll"
		m_pValidatorScopeVector = new OwnedVector<ValidatorScope*>();
#line 39 "../../../Source/Core/Validator.nll"
		m_pCurrentNamespaceNode = pProject->m_pRootNamespaceNode;
#line 41 "../../../Source/Core/Validator.nll"
		m_pResolver = new Resolver();
	}

#line 44 "../../../Source/Core/Validator.nll"
	void Validator::PreparseNamespaces(NamespaceNode* pCurrentNode, AST* pAST)
	{
		AST* pChild = pAST->m_pFirstChild;
#line 47 "../../../Source/Core/Validator.nll"
		while (pChild != 0)
		{
#line 49 "../../../Source/Core/Validator.nll"
			if (pChild->m_eType == AST::Type::NAMESPACE_DECL)
			{
				NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pChild);
				NamespaceNode* pNextNamespaceNode = pCurrentNode->GetOrCreateChild(pNamespaceDecl);
#line 53 "../../../Source/Core/Validator.nll"
				PreparseNamespaces(pNextNamespaceNode, pChild);
			}
#line 55 "../../../Source/Core/Validator.nll"
			pChild = pChild->m_pNextSibling;
		}
	}

#line 59 "../../../Source/Core/Validator.nll"
	bool Validator::Validate()
	{
		InternalString* sTemp = new InternalString("");
#line 64 "../../../Source/Core/Validator.nll"
		for (int i = 0; i < m_pProject->m_pTranslationUnitVector->GetSize(); i++)
		{
			TranslationUnit* pTranslationUnit = m_pProject->m_pTranslationUnitVector->Get(i);
#line 67 "../../../Source/Core/Validator.nll"
			PreparseNamespaces(m_pProject->m_pRootNamespaceNode, pTranslationUnit);
		}
#line 71 "../../../Source/Core/Validator.nll"
		for (int i = 0; i < m_pProject->m_pTranslationUnitVector->GetSize(); i++)
		{
			TranslationUnit* pTranslationUnit = m_pProject->m_pTranslationUnitVector->Get(i);
#line 74 "../../../Source/Core/Validator.nll"
			m_pResolver->BuildForRoot(pTranslationUnit);
		}
#line 77 "../../../Source/Core/Validator.nll"
		for (int i = 0; i < m_pProject->m_pTranslationUnitVector->GetSize(); i++)
		{
			TranslationUnit* pTranslationUnit = m_pProject->m_pTranslationUnitVector->Get(i);
#line 80 "../../../Source/Core/Validator.nll"
			pTranslationUnit->PreValidate(this, 0);
		}
#line 83 "../../../Source/Core/Validator.nll"
		for (int i = 0; i < m_pProject->m_pTranslationUnitVector->GetSize(); i++)
		{
			TranslationUnit* pTranslationUnit = m_pProject->m_pTranslationUnitVector->Get(i);
#line 86 "../../../Source/Core/Validator.nll"
			pTranslationUnit->Validate(this, 0);
		}
#line 89 "../../../Source/Core/Validator.nll"
		for (int i = 0; i < m_pValidatorErrorVector->GetSize(); i++)
		{
			ValidatorError* pValidatorError = m_pValidatorErrorVector->Get(i);
#line 92 "../../../Source/Core/Validator.nll"
			sTemp->Set(pValidatorError->m_sFile->GetExternalString());
#line 93 "../../../Source/Core/Validator.nll"
			sTemp->Append(":");
#line 94 "../../../Source/Core/Validator.nll"
			sTemp->AppendInt(pValidatorError->m_nLine);
#line 95 "../../../Source/Core/Validator.nll"
			sTemp->Append(":");
#line 96 "../../../Source/Core/Validator.nll"
			sTemp->AppendInt(pValidatorError->m_nColumn);
#line 97 "../../../Source/Core/Validator.nll"
			sTemp->Append(" Error: ");
#line 98 "../../../Source/Core/Validator.nll"
			sTemp->Append(pValidatorError->m_sError->GetExternalString());
#line 99 "../../../Source/Core/Validator.nll"
			Console::Log(sTemp->GetExternalString());
		}
#line 102 "../../../Source/Core/Validator.nll"
		if (m_pValidatorErrorVector->GetSize() > 0)
		{
#line 104 "../../../Source/Core/Validator.nll"
			sTemp->Set("");
#line 105 "../../../Source/Core/Validator.nll"
			sTemp->AppendInt(m_pValidatorErrorVector->GetSize());
#line 106 "../../../Source/Core/Validator.nll"
			sTemp->Append(" errors");
#line 107 "../../../Source/Core/Validator.nll"
			Console::Log(sTemp->GetExternalString());
		}
		if (sTemp) delete sTemp;
#line 110 "../../../Source/Core/Validator.nll"
		return m_pValidatorErrorVector->GetSize() == 0;
	}

#line 113 "../../../Source/Core/Validator.nll"
	void Validator::AddError(const char* sError, InternalString* sFile, int nLine, int nColumn)
	{
		ValidatorError* pValidatorError = new ValidatorError();
#line 116 "../../../Source/Core/Validator.nll"
		pValidatorError->m_sError = new InternalString(sError);
#line 117 "../../../Source/Core/Validator.nll"
		if (sFile == 0)
#line 118 "../../../Source/Core/Validator.nll"
			pValidatorError->m_sFile = new InternalString("-- no file --");
		else
#line 120 "../../../Source/Core/Validator.nll"
			pValidatorError->m_sFile = new InternalString(sFile->GetExternalString());
#line 121 "../../../Source/Core/Validator.nll"
		pValidatorError->m_nLine = nLine;
#line 122 "../../../Source/Core/Validator.nll"
		pValidatorError->m_nColumn = nColumn;
		NumbatLogic::ValidatorError* __3001553964 = pValidatorError;
#line 123 "../../../Source/Core/Validator.nll"
		pValidatorError = 0;
#line 123 "../../../Source/Core/Validator.nll"
		m_pValidatorErrorVector->PushBack(__3001553964);
		if (pValidatorError) delete pValidatorError;
	}

#line 127 "../../../Source/Core/Validator.nll"
	void Validator::ValidateSubtree(AST* pRoot)
	{
#line 129 "../../../Source/Core/Validator.nll"
		pRoot->PreValidate(this, 0);
#line 130 "../../../Source/Core/Validator.nll"
		pRoot->Validate(this, 0);
	}

#line 133 "../../../Source/Core/Validator.nll"
	void Validator::BeginScope(Scope* pScope)
	{
		ValidatorScope* pValidatorScope = new ValidatorScope(pScope);
		NumbatLogic::ValidatorScope* __3052106978 = pValidatorScope;
#line 136 "../../../Source/Core/Validator.nll"
		pValidatorScope = 0;
#line 136 "../../../Source/Core/Validator.nll"
		m_pValidatorScopeVector->PushBack(__3052106978);
		if (pValidatorScope) delete pValidatorScope;
	}

#line 139 "../../../Source/Core/Validator.nll"
	void Validator::AddVarDecl(VarDecl* pVarDecl)
	{
		ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType(m_pResolver);
#line 142 "../../../Source/Core/Validator.nll"
		if (pValueType != 0)
#line 143 "../../../Source/Core/Validator.nll"
			if (pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE && pValueType->m_ePointerType == TypeRef::PointerType::OWNED)
			{
				int nIndex = m_pValidatorScopeVector->GetSize() - 1;
#line 146 "../../../Source/Core/Validator.nll"
				Assert::Plz(nIndex >= 0);
				ValidatorScope* pValidatorScope = m_pValidatorScopeVector->Get(nIndex);
#line 149 "../../../Source/Core/Validator.nll"
				pValidatorScope->m_pVarDeclVector->PushBack(pVarDecl);
			}
		if (pValueType) delete pValueType;
	}

#line 153 "../../../Source/Core/Validator.nll"
	void Validator::EndScope(Scope* pScope)
	{
		ValidatorScope* pValidatorScope = m_pValidatorScopeVector->PopBack();
#line 156 "../../../Source/Core/Validator.nll"
		Assert::Plz(pValidatorScope != 0);
#line 157 "../../../Source/Core/Validator.nll"
		Assert::Plz(pValidatorScope->m_pScope == pScope);
		AST* pCheck = pScope;
#line 160 "../../../Source/Core/Validator.nll"
		while (pCheck != 0 && pCheck->m_eType == AST::Type::AST_SCOPE)
		{
#line 162 "../../../Source/Core/Validator.nll"
			pCheck = pCheck->m_pLastChild;
		}
#line 164 "../../../Source/Core/Validator.nll"
		if (pCheck != 0)
#line 165 "../../../Source/Core/Validator.nll"
			if (pCheck->m_eType == AST::Type::AST_RETURN_STMT || pCheck->m_eType == AST::Type::AST_CONTINUE_STMT || pCheck->m_eType == AST::Type::AST_BREAK_STMT)
			{
				if (pValidatorScope) delete pValidatorScope;
#line 166 "../../../Source/Core/Validator.nll"
				return;
			}
#line 168 "../../../Source/Core/Validator.nll"
		if (pValidatorScope->m_pVarDeclVector->GetSize() > 0)
		{
			VarDeclDescope* pVarDeclDescope = new VarDeclDescope();
#line 171 "../../../Source/Core/Validator.nll"
			for (int i = 0; i < pValidatorScope->m_pVarDeclVector->GetSize(); i++)
			{
				VarDecl* pVarDecl = pValidatorScope->m_pVarDeclVector->Get(i);
#line 174 "../../../Source/Core/Validator.nll"
				pVarDeclDescope->m_pVarDeclVector->PushBack(pVarDecl);
			}
			NumbatLogic::VarDeclDescope* __2691051646 = pVarDeclDescope;
#line 176 "../../../Source/Core/Validator.nll"
			pVarDeclDescope = 0;
#line 176 "../../../Source/Core/Validator.nll"
			pScope->AddChild(__2691051646);
			if (pVarDeclDescope) delete pVarDeclDescope;
		}
		if (pValidatorScope) delete pValidatorScope;
	}

#line 180 "../../../Source/Core/Validator.nll"
	void Validator::InjectCleanup(AST* pBreakOrContinueOrReturn)
	{
		Identifier* pDisownedIdentifier = 0;
#line 184 "../../../Source/Core/Validator.nll"
		if (pBreakOrContinueOrReturn->m_eType == AST::Type::AST_RETURN_STMT)
		{
			ReturnStmt* pReturnStmt = (ReturnStmt*)(pBreakOrContinueOrReturn);
#line 188 "../../../Source/Core/Validator.nll"
			if (pReturnStmt->m_pExpression != 0 && pReturnStmt->m_pExpression->m_eType == AST::Type::AST_DISOWN_EXP)
			{
				DisownExpr* pDisownExpr = (DisownExpr*)(pReturnStmt->m_pExpression);
#line 191 "../../../Source/Core/Validator.nll"
				if (pDisownExpr->m_pExpression->m_eType == AST::Type::AST_IDENTIFIER)
				{
#line 193 "../../../Source/Core/Validator.nll"
					pDisownedIdentifier = (Identifier*)(pDisownExpr->m_pExpression);
				}
			}
		}
		VarDeclDescope* pVarDeclDescope = new VarDeclDescope();
#line 200 "../../../Source/Core/Validator.nll"
		for (int i = m_pValidatorScopeVector->GetSize() - 1; i >= 0; i--)
		{
			ValidatorScope* pValidatorScope = m_pValidatorScopeVector->Get(i);
#line 203 "../../../Source/Core/Validator.nll"
			for (int j = 0; j < pValidatorScope->m_pVarDeclVector->GetSize(); j++)
			{
				VarDecl* pVarDecl = pValidatorScope->m_pVarDeclVector->Get(j);
#line 206 "../../../Source/Core/Validator.nll"
				if (pDisownedIdentifier != 0)
				{
#line 208 "../../../Source/Core/Validator.nll"
					if (ExternalString::Equal(pVarDecl->m_pNameToken->GetString(), pDisownedIdentifier->m_pFirstToken->GetString()))
#line 209 "../../../Source/Core/Validator.nll"
						continue;
				}
#line 211 "../../../Source/Core/Validator.nll"
				pVarDeclDescope->m_pVarDeclVector->PushBack(pVarDecl);
			}
#line 214 "../../../Source/Core/Validator.nll"
			if (pBreakOrContinueOrReturn->m_eType == AST::Type::AST_RETURN_STMT)
			{
#line 216 "../../../Source/Core/Validator.nll"
				if (pValidatorScope->m_pScope->m_pParent->m_eType == AST::Type::AST_FUNCTION_DECL)
#line 217 "../../../Source/Core/Validator.nll"
					break;
			}
			else
			{
#line 221 "../../../Source/Core/Validator.nll"
				if (pValidatorScope->m_pScope->m_pParent->m_eType == AST::Type::AST_FOR_STMT || pValidatorScope->m_pScope->m_pParent->m_eType == AST::Type::AST_WHILE_STMT || pValidatorScope->m_pScope->m_pParent->m_eType == AST::Type::AST_SWITCH_STMT)
#line 224 "../../../Source/Core/Validator.nll"
					break;
			}
		}
#line 228 "../../../Source/Core/Validator.nll"
		if (pVarDeclDescope->m_pVarDeclVector->GetSize() > 0)
		{
			AST* pParent = pBreakOrContinueOrReturn->m_pParent;
			NumbatLogic::VarDeclDescope* __2699050750 = pVarDeclDescope;
#line 231 "../../../Source/Core/Validator.nll"
			pVarDeclDescope = 0;
#line 231 "../../../Source/Core/Validator.nll"
			pParent->AddChildBefore(__2699050750, pBreakOrContinueOrReturn);
		}
		if (pVarDeclDescope) delete pVarDeclDescope;
	}

#line 239 "../../../Source/Core/Validator.nll"
	void Validator::BeginNamespace(const char* sxName)
	{
#line 241 "../../../Source/Core/Validator.nll"
		m_pCurrentNamespaceNode = m_pCurrentNamespaceNode->GetChild(sxName);
#line 242 "../../../Source/Core/Validator.nll"
		Assert::Plz(m_pCurrentNamespaceNode != 0);
	}

#line 245 "../../../Source/Core/Validator.nll"
	void Validator::EndNamespace(const char* sxName)
	{
#line 247 "../../../Source/Core/Validator.nll"
		Assert::Plz(m_pCurrentNamespaceNode->m_sName->IsEqual(sxName));
#line 248 "../../../Source/Core/Validator.nll"
		Assert::Plz(m_pCurrentNamespaceNode->m_pParent != 0);
#line 249 "../../../Source/Core/Validator.nll"
		m_pCurrentNamespaceNode = m_pCurrentNamespaceNode->m_pParent;
	}

#line 23 "../../../Source/Core/Validator.nll"
	Validator::~Validator()
	{
		if (m_pValidatorErrorVector) delete m_pValidatorErrorVector;
		if (m_pValidatorScopeVector) delete m_pValidatorScopeVector;
		if (m_pResolver) delete m_pResolver;
	}

}

