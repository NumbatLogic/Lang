#include "Resolver.hpp"
#include "SymbolScope.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "Symbol.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../AST/AST.hpp"
#include "../AST/MemberClassDecl.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "../AST/ClassDecl.hpp"
#include "../AST/GenericTypeDecl.hpp"
#include "../Token.hpp"
#include "../AST/MemberVarDecl.hpp"
#include "../AST/VarDecl.hpp"
#include "../AST/MemberFunctionDecl.hpp"
#include "../AST/FunctionDecl.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../AST/MemberEnumDecl.hpp"
#include "../AST/EnumDecl.hpp"
#include "../AST/DelegateDecl.hpp"
#include "../AST/NamespaceDecl.hpp"
#include "../NamespaceNode.hpp"
#include "../AST/EnumDeclValue.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"

namespace NumbatLogic
{
	class Resolver;
	class SymbolScope;
	template <class T>
	class OwnedVector;
	class Symbol;
	template <class T>
	class Vector;
	class ClassDecl;
	class MemberClassDecl;
	class ExternalString;
	class AST;
	class GenericTypeDecl;
	class Token;
	class MemberVarDecl;
	class MemberFunctionDecl;
	class InternalString;
	class MemberEnumDecl;
	class DelegateDecl;
	class NamespaceDecl;
	class NamespaceNode;
	class EnumDecl;
	class FunctionDecl;
	class VarDecl;
	class EnumDeclValue;
	class Assert;
}
#line 0 "../../../Source/Core/Semantic/Resolver.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Semantic/Resolver.nll"
	Resolver::Resolver()
	{
		m_pGlobalScope = 0;
		m_pScopeVector = 0;
		m_pBuildTempSymbolVector = 0;
		m_pGlobalScope = new SymbolScope();
		m_pGlobalScope->m_eKind = SymbolScope::Kind::GLOBAL;
		m_pGlobalScope->m_pParent = 0;
		m_pGlobalScope->m_pOwnerAST = 0;
		m_pScopeVector = new OwnedVector<SymbolScope*>();
		m_pBuildTempSymbolVector = new Vector<Symbol*>();
	}

	ClassDecl* Resolver::GetClassDeclFromOwnerAST(AST* pOwner)
	{
		if (pOwner == 0)
			return 0;
		if (pOwner->m_eType == AST::Type::AST_CLASS_DECL)
			return (ClassDecl*)(pOwner);
		if (pOwner->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
		{
			MemberClassDecl* pMember = (MemberClassDecl*)(pOwner);
			return pMember->m_pClassDecl;
		}
		return 0;
	}

	SymbolScope* Resolver::CreateChildScope(AST* pNode, SymbolScope* pParent, SymbolScope::Kind eKind)
	{
		SymbolScope* pOwnedScope = new SymbolScope();
		NumbatLogic::SymbolScope* __1793915775 = pOwnedScope;
		pOwnedScope = 0;
		SymbolScope* pNewScope = m_pScopeVector->PushBack(__1793915775);
		pNewScope->m_eKind = eKind;
		pNewScope->m_pParent = pParent;
		pNewScope->m_pOwnerAST = pNode;
		pNode->m_pSymbolScope = pNewScope;
		if (pOwnedScope) delete pOwnedScope;
		return pNewScope;
	}

	void Resolver::AddSymbolToScope(SymbolScope* pScope, const char* sShortName, Symbol::Kind eKind, AST* pDeclAST, const char* sQualifiedName)
	{
		if (pScope == 0 || sShortName == 0)
			return;
		const char* sQual = (sQualifiedName != 0 && !ExternalString::Equal(sQualifiedName, "")) ? sQualifiedName : sShortName;
		Symbol* pOwnedSymbol = new Symbol();
		pOwnedSymbol->m_eKind = eKind;
		pOwnedSymbol->m_sShortName = sShortName;
		pOwnedSymbol->m_sQualifiedName = sQual;
		pOwnedSymbol->m_pDeclAST = pDeclAST;
		pOwnedSymbol->m_pScope = 0;
		NumbatLogic::Symbol* __3172268842 = pOwnedSymbol;
		pOwnedSymbol = 0;
		pScope->AddSymbol(sShortName, __3172268842);
		if (pOwnedSymbol) delete pOwnedSymbol;
	}

	SymbolScope* Resolver::GetEnclosingScope(AST* pNode)
	{
		if (pNode == 0)
			return 0;
		AST* pWalk = pNode;
		while (pWalk != 0)
		{
			if (pWalk->m_eType == AST::Type::AST_CLASS_DECL || pWalk->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
			{
				if (pWalk->m_pSymbolScope == 0)
					EnsureClassScope(pWalk);
			}
			if (pWalk->m_pSymbolScope != 0)
				return pWalk->m_pSymbolScope;
			pWalk = pWalk->m_pParent;
		}
		return m_pGlobalScope;
	}

	void Resolver::EnsureClassScope(AST* pOwnerNode)
	{
		if (pOwnerNode == 0 || pOwnerNode->m_pSymbolScope != 0)
			return;
		ClassDecl* pClassDecl = GetClassDeclFromOwnerAST(pOwnerNode);
		if (pClassDecl == 0)
			return;
		SymbolScope* pEnclosing = m_pGlobalScope;
		AST* pWalk = pOwnerNode->m_pParent;
		while (pWalk != 0)
		{
			if (pWalk->m_eType == AST::Type::AST_CLASS_DECL || pWalk->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
			{
				if (pWalk->m_pSymbolScope == 0)
					EnsureClassScope(pWalk);
			}
			if (pWalk->m_pSymbolScope != 0)
			{
				pEnclosing = pWalk->m_pSymbolScope;
#line 114 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}
			pWalk = pWalk->m_pParent;
		}
		SymbolScope* pClassScope = CreateChildScope(pOwnerNode, pEnclosing, SymbolScope::Kind::CLASS);
		AddGenericParamsToScope(pClassDecl, pClassScope);
		AST* pChild = pClassDecl->m_pFirstChild;
		while (pChild != 0)
		{
			AddMemberSymbolToScope(pChild, pClassScope);
			pChild = pChild->m_pNextSibling;
		}
	}

	void Resolver::AddGenericParamsToScope(ClassDecl* pClassDecl, SymbolScope* pScope)
	{
		if (pClassDecl == 0 || pScope == 0 || pClassDecl->m_pGenericTypeDeclVector == 0)
			return;
		for (int i = 0; i < pClassDecl->m_pGenericTypeDeclVector->GetSize(); i++)
		{
			GenericTypeDecl* pGenericTypeDecl = pClassDecl->m_pGenericTypeDeclVector->Get(i);
			const char* sGenericName = pGenericTypeDecl->m_pFirstToken->GetString();
			AddSymbolToScope(pScope, sGenericName, Symbol::Kind::GENERIC_PARAM, pGenericTypeDecl, 0);
		}
	}

	void Resolver::AddMemberSymbolToScope(AST* pMemberNode, SymbolScope* pScope)
	{
		if (pMemberNode == 0 || pScope == 0)
			return;
		if (pMemberNode->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
		{
			MemberVarDecl* pMemberVar = (MemberVarDecl*)(pMemberNode);
			if (pMemberVar->m_pVarDecl != 0)
				AddSymbolToScope(pScope, pMemberVar->m_pVarDecl->m_pNameToken->GetString(), Symbol::Kind::VAR, pMemberNode, 0);
		}
		else
			if (pMemberNode->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
			{
				MemberFunctionDecl* pMemberFunc = (MemberFunctionDecl*)(pMemberNode);
				if (pMemberFunc->m_pFunctionDecl != 0)
					AddSymbolToScope(pScope, pMemberFunc->m_pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::METHOD, pMemberNode, 0);
			}
			else
				if (pMemberNode->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
				{
					MemberClassDecl* pMemberClass = (MemberClassDecl*)(pMemberNode);
					if (pMemberClass->m_pClassDecl != 0)
					{
						const char* sName = pMemberClass->m_pClassDecl->m_pNameToken->GetString();
						InternalString* sTemp = new InternalString("");
						pMemberClass->m_pClassDecl->AppendFullyQualifiedName(sTemp);
						AddSymbolToScope(pScope, sName, Symbol::Kind::CLASS, pMemberNode, sTemp->GetExternalString());
						if (sTemp) delete sTemp;
					}
				}
				else
					if (pMemberNode->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
					{
						MemberEnumDecl* pMemberEnum = (MemberEnumDecl*)(pMemberNode);
						if (pMemberEnum->m_pEnumDecl != 0)
							AddSymbolToScope(pScope, pMemberEnum->m_pEnumDecl->m_pNameToken->GetString(), Symbol::Kind::ENUM, pMemberNode, 0);
					}
					else
						if (pMemberNode->m_eType == AST::Type::DELEGATE_DECL)
						{
							DelegateDecl* pDelegateDecl = (DelegateDecl*)(pMemberNode);
							if (pDelegateDecl->m_pFunctionDecl != 0 && pDelegateDecl->m_pFunctionDecl->m_pNameToken != 0)
								AddSymbolToScope(pScope, pDelegateDecl->m_pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::DELEGATE, pMemberNode, 0);
						}
	}

	void Resolver::BuildForRoot(AST* pRoot)
	{
		if (pRoot == 0)
			return;
		pRoot->m_pSymbolScope = m_pGlobalScope;
		BuildForNode(pRoot, m_pGlobalScope);
	}

	void Resolver::BuildForNode(AST* pNode, SymbolScope* pScope)
	{
		if (pNode == 0 || pScope == 0)
			return;
		SymbolScope* pCurrentScope = pScope;
		switch (pNode->m_eType)
		{
			case AST::Type::NAMESPACE_DECL:
			{
				NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pNode);
				const char* sName = pNamespaceDecl->m_pNameToken->GetString();
				SymbolScope* pNamespaceScope = pScope->FindNamespaceScope(sName);
				if (pNamespaceScope != 0)
				{
					pNode->m_pSymbolScope = pNamespaceScope;
					pCurrentScope = pNamespaceScope;
#line 218 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}
				const char* sQual = sName;
				if (pNamespaceDecl->m_pNamespaceNode != 0)
				{
					InternalString* sTemp = new InternalString("");
					pNamespaceDecl->m_pNamespaceNode->AppendFullyQualifiedName(sTemp);
					sQual = sTemp->GetExternalString();
					if (sTemp) delete sTemp;
				}
				AddSymbolToScope(pScope, sName, Symbol::Kind::NAMESPACE, pNode, sQual);
				pNamespaceScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::NAMESPACE);
				pCurrentScope = pNamespaceScope;
				m_pBuildTempSymbolVector->Clear();
				pScope->FindInThisScope(sName, m_pBuildTempSymbolVector);
				if (m_pBuildTempSymbolVector->GetSize() > 0)
				{
					Symbol* pLast = m_pBuildTempSymbolVector->Get(m_pBuildTempSymbolVector->GetSize() - 1);
					pLast->m_pScope = pNamespaceScope;
				}
#line 243 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_CLASS_DECL:
			{
				ClassDecl* pClassDecl = (ClassDecl*)(pNode);
				bool bIsInnerOfMemberClass = (pClassDecl->m_pParent != 0 && pClassDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_CLASS_DECL);
				if (!bIsInnerOfMemberClass)
				{
					const char* sName = pClassDecl->m_pNameToken->GetString();
					InternalString* sTemp = new InternalString("");
					pClassDecl->AppendFullyQualifiedName(sTemp);
					AddSymbolToScope(pScope, sName, Symbol::Kind::CLASS, pNode, sTemp->GetExternalString());
					if (sTemp) delete sTemp;
				}
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::CLASS);
				SymbolScope* pClassScope = pCurrentScope;
				AddGenericParamsToScope(pClassDecl, pClassScope);
#line 265 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_ENUM_DECL:
			{
				EnumDecl* pEnumDecl = (EnumDecl*)(pNode);
				if (pEnumDecl->m_pParent != 0 && pEnumDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
#line 275 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				AddSymbolToScope(pScope, pEnumDecl->m_pNameToken->GetString(), Symbol::Kind::ENUM, pNode, 0);
#line 277 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_GENERIC_TYPE_DECL:
			{
				GenericTypeDecl* pGenericTypeDecl = (GenericTypeDecl*)(pNode);
				AddSymbolToScope(pScope, pGenericTypeDecl->m_pFirstToken->GetString(), Symbol::Kind::GENERIC_PARAM, pNode, 0);
#line 287 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_FUNCTION_DECL:
			{
				FunctionDecl* pFunctionDecl = (FunctionDecl*)(pNode);
				if (pFunctionDecl->m_pParent != 0 && (pFunctionDecl->m_pParent->m_eType == AST::Type::DELEGATE_DECL || pFunctionDecl->m_pParent->m_eType == AST::Type::AST_TOR_DECL))
#line 298 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				bool bIsInnerOfMember = (pFunctionDecl->m_pParent != 0 && pFunctionDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL);
				if (!bIsInnerOfMember)
					AddSymbolToScope(pScope, pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::FUNCTION, pNode, 0);
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::FUNCTION);
#line 310 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_VAR_DECL:
			{
				VarDecl* pVarDecl = (VarDecl*)(pNode);
				if (pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
#line 322 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				AddSymbolToScope(pScope, pVarDecl->m_pNameToken->GetString(), Symbol::Kind::VAR, pNode, 0);
#line 325 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::DELEGATE_DECL:
			{
				DelegateDecl* pDelegate = (DelegateDecl*)(pNode);
				if (pDelegate->m_pFunctionDecl != 0)
					AddSymbolToScope(pScope, pDelegate->m_pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::DELEGATE, pNode, 0);
#line 332 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_MEMBER_FUNCTION_DECL:
			{
				AddMemberSymbolToScope(pNode, pCurrentScope);
#line 337 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_MEMBER_VAR_DECL:
			{
				AddMemberSymbolToScope(pNode, pCurrentScope);
#line 342 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_MEMBER_CLASS_DECL:
			{
				MemberClassDecl* pMemberClass = (MemberClassDecl*)(pNode);
				if (pMemberClass->m_pClassDecl != 0)
				{
					AddMemberSymbolToScope(pNode, pCurrentScope);
					pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::CLASS);
				}
#line 352 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_MEMBER_ENUM_DECL:
			{
				AddMemberSymbolToScope(pNode, pCurrentScope);
#line 357 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::ENUM_DECL_VALUE:
			{
				EnumDeclValue* pEnumValue = (EnumDeclValue*)(pNode);
				AddSymbolToScope(pScope, pEnumValue->m_pFirstToken->GetString(), Symbol::Kind::ENUM_VALUE, pNode, 0);
#line 363 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_SCOPE:
			{
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::BLOCK);
#line 368 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_FOR_STMT:
			{
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::BLOCK);
#line 374 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_TOR_DECL:
			{
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::FUNCTION);
#line 380 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

		}
		AST* pChild = pNode->m_pFirstChild;
		while (pChild != 0)
		{
			AST* pNext = pChild->m_pNextSibling;
			BuildForNode(pChild, pCurrentScope);
			pChild = pNext;
		}
	}

	void Resolver::ResolveInScopeChainNoBaseClasses(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut)
	{
		Assert::Plz(pOut != 0);
		pOut->Clear();
		SymbolScope* pScope = pStartScope;
		while (pScope != 0)
		{
			pScope->FindInThisScope(sName, pOut);
			if (pOut->GetSize() > 0)
				return;
			pScope = pScope->m_pParent;
		}
	}

	void Resolver::ResolveInScopeChain(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut)
	{
		Assert::Plz(pOut != 0);
		pOut->Clear();
		SymbolScope* pScope = pStartScope;
		while (pScope != 0)
		{
			pScope->FindInThisScope(sName, pOut);
			if (pOut->GetSize() > 0)
				return;
			if (pScope->m_eKind == SymbolScope::Kind::CLASS)
			{
				ClassDecl* pClass = GetClassDeclFromOwnerAST(pScope->m_pOwnerAST);
				if (pClass != 0)
				{
					ClassDecl* pBase = pClass->GetBaseClassDeclForScopeLookup(this);
					while (pBase != 0)
					{
						if (pBase->m_pSymbolScope != 0)
						{
							pBase->m_pSymbolScope->FindInThisScope(sName, pOut);
							if (pOut->GetSize() > 0)
								return;
						}
						pBase = pBase->GetBaseClassDeclForScopeLookup(this);
					}
				}
			}
			pScope = pScope->m_pParent;
		}
	}

	void Resolver::ResolveFromNode(AST* pNode, const char* sName, Vector<Symbol*>* pOut)
	{
		SymbolScope* pScope = GetEnclosingScope(pNode);
		ResolveInScopeChain(sName, pScope, pOut);
	}

	Resolver::~Resolver()
	{
		if (m_pGlobalScope) delete m_pGlobalScope;
		if (m_pScopeVector) delete m_pScopeVector;
		if (m_pBuildTempSymbolVector) delete m_pBuildTempSymbolVector;
	}

}

